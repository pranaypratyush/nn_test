#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
    char c;
    if (argc != 3)
    {
        cout << " Usage: displayimage ImageToLoadAndDisplay" << endl;
        return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); // Read the file

    char ***allvals = new char**[256];
    for (int i = 0; i < 256; i++)
    {
        allvals[i] = new char*[256];

        for (int j = 0; j < 256; j++)
        {
            allvals[i][j] = new char[256];
        }
    }

    ifstream f;
    f.open(argv[2]);

    if (f)
    {
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                for (int k = 0; k < 256; k++)
                {
                    if (!f.eof())
                    {
                        f >> c;
                        allvals[i][j][k] = c - '0';
                    }
                }
            }
        }
    }
    else
    {
        cerr << ("Unable to open values file.");

    }

    for (int j = 0; j < image.rows; j++)
    {
        for (int i = 0; i < image.cols; i++)
        {
            int k = allvals[image.at<Vec3b>(j, i).val[0]][image.at<Vec3b>(j, i).val[1]][image.at<Vec3b>(j, i).val[2]];

            if (k == 1)
            {
                image.at<Vec3b>(j, i).val[0] = 255;
                image.at<Vec3b>(j, i).val[1] = 255;
                image.at<Vec3b>(j, i).val[2] = 255;
            }

            if (k == 0)
            {
                image.at<Vec3b>(j, i).val[0] = 0;
                image.at<Vec3b>(j, i).val[1] = 0;
                image.at<Vec3b>(j, i).val[2] = 0;
            }

            if (k == 2)
            {
                image.at<Vec3b>(j, i).val[0] = 0;
                image.at<Vec3b>(j, i).val[1] = 0;
                image.at<Vec3b>(j, i).val[2] = 0;
            }
        }
    }
    imshow("Image",image);
    waitKey(0);
}