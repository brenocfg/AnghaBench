#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num; int denom; } ;

/* Variables and functions */
 int DEFAULT_QUALITY ; 
 size_t DEFAULT_SUBSAMP ; 
 int /*<<< orphan*/  exit (int) ; 
 int numScalingFactors ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* scalingFactors ; 
 char** subsampName ; 

void usage(char *programName)
{
  int i;

  printf("\nUSAGE: %s <Input image> <Output image> [options]\n\n",
         programName);

  printf("Input and output images can be in Windows BMP or PBMPLUS (PPM/PGM) format.  If\n");
  printf("either filename ends in a .jpg extension, then the TurboJPEG API will be used\n");
  printf("to compress or decompress the image.\n\n");

  printf("Compression Options (used if the output image is a JPEG image)\n");
  printf("--------------------------------------------------------------\n\n");

  printf("-subsamp <444|422|420|gray> = Apply this level of chrominance subsampling when\n");
  printf("     compressing the output image.  The default is to use the same level of\n");
  printf("     subsampling as in the input image, if the input image is also a JPEG\n");
  printf("     image, or to use grayscale if the input image is a grayscale non-JPEG\n");
  printf("     image, or to use %s subsampling otherwise.\n\n",
         subsampName[DEFAULT_SUBSAMP]);

  printf("-q <1-100> = Compress the output image with this JPEG quality level\n");
  printf("     (default = %d).\n\n", DEFAULT_QUALITY);

  printf("Decompression Options (used if the input image is a JPEG image)\n");
  printf("---------------------------------------------------------------\n\n");

  printf("-scale M/N = Scale the input image by a factor of M/N when decompressing it.\n");
  printf("(M/N = ");
  for (i = 0; i < numScalingFactors; i++) {
    printf("%d/%d", scalingFactors[i].num, scalingFactors[i].denom);
    if (numScalingFactors == 2 && i != numScalingFactors - 1)
      printf(" or ");
    else if (numScalingFactors > 2) {
      if (i != numScalingFactors - 1)
        printf(", ");
      if (i == numScalingFactors - 2)
        printf("or ");
    }
  }
  printf(")\n\n");

  printf("-hflip, -vflip, -transpose, -transverse, -rot90, -rot180, -rot270 =\n");
  printf("     Perform one of these lossless transform operations on the input image\n");
  printf("     prior to decompressing it (these options are mutually exclusive.)\n\n");

  printf("-grayscale = Perform lossless grayscale conversion on the input image prior\n");
  printf("     to decompressing it (can be combined with the other transform operations\n");
  printf("     above.)\n\n");

  printf("-crop WxH+X+Y = Perform lossless cropping on the input image prior to\n");
  printf("     decompressing it.  X and Y specify the upper left corner of the cropping\n");
  printf("     region, and W and H specify the width and height of the cropping region.\n");
  printf("     X and Y must be evenly divible by the MCU block size (8x8 if the input\n");
  printf("     image was compressed using no subsampling or grayscale, 16x8 if it was\n");
  printf("     compressed using 4:2:2 subsampling, or 16x16 if it was compressed using\n");
  printf("     4:2:0 subsampling.)\n\n");

  printf("General Options\n");
  printf("---------------\n\n");

  printf("-fastupsample = Use the fastest chrominance upsampling algorithm available in\n");
  printf("     the underlying codec.\n\n");

  printf("-fastdct = Use the fastest DCT/IDCT algorithms available in the underlying\n");
  printf("     codec.\n\n");

  printf("-accuratedct = Use the most accurate DCT/IDCT algorithms available in the\n");
  printf("     underlying codec.\n\n");

  exit(1);
}