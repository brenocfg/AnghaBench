#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ gdPoint ;
typedef  scalar_t__ gdImagePtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdFontGiant ; 
 int /*<<< orphan*/  gdFontSmall ; 
 int /*<<< orphan*/  gdImageArc (scalar_t__,int,int,int,int,int,int,int) ; 
 int gdImageColorAllocate (scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  gdImageColorTransparent (scalar_t__,int) ; 
 int /*<<< orphan*/  gdImageCopyResized (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ gdImageCreateFromPng (int /*<<< orphan*/ *) ; 
 scalar_t__ gdImageCreateTrueColor (int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (scalar_t__) ; 
 int /*<<< orphan*/  gdImageFill (scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  gdImageFilledPolygon (scalar_t__,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gdImageInterlace (scalar_t__,int) ; 
 int /*<<< orphan*/  gdImageLine (scalar_t__,int,int,int,int,int) ; 
 int /*<<< orphan*/  gdImagePng (scalar_t__,int /*<<< orphan*/ *) ; 
 int gdImageSX (scalar_t__) ; 
 int gdImageSY (scalar_t__) ; 
 int /*<<< orphan*/  gdImageSetBrush (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gdImageSetStyle (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  gdImageString (scalar_t__,int /*<<< orphan*/ ,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  gdImageStringUp (scalar_t__,int /*<<< orphan*/ ,int,int,unsigned char*,int) ; 
 int gdStyledBrushed ; 
 int /*<<< orphan*/  stderr ; 

int
main (void)
{
  /* Input and output files */
  FILE *in;
  FILE *out;

  /* Input and output images */
  gdImagePtr im_in = 0, im_out = 0;

  /* Brush image */
  gdImagePtr brush;

  /* Color indexes */
  int white;
  int blue;
  int red;
  int green;

  /* Points for polygon */
  gdPoint points[3];

  /* Create output image, 256 by 256 pixels, true color. */
  im_out = gdImageCreateTrueColor (256, 256);
  /* First color allocated is background. */
  white = gdImageColorAllocate (im_out, 255, 255, 255);

  /* Set transparent color. */
  gdImageColorTransparent (im_out, white);

  /* Try to load demoin.png and paste part of it into the
     output image. */
  in = fopen ("demoin.png", "rb");
  if (!in)
    {
      fprintf (stderr, "Can't load source image; this demo\n");
      fprintf (stderr, "is much more impressive if demoin.png\n");
      fprintf (stderr, "is available.\n");
      im_in = 0;
    }
  else
    {
      im_in = gdImageCreateFromPng (in);
      fclose (in);
      /* Now copy, and magnify as we do so */
      gdImageCopyResized (im_out, im_in,
			  32, 32, 0, 0, 192, 192, 255, 255);
    }
  red = gdImageColorAllocate (im_out, 255, 0, 0);
  green = gdImageColorAllocate (im_out, 0, 255, 0);
  blue = gdImageColorAllocate (im_out, 0, 0, 255);
  /* Rectangle */
  gdImageLine (im_out, 16, 16, 240, 16, green);
  gdImageLine (im_out, 240, 16, 240, 240, green);
  gdImageLine (im_out, 240, 240, 16, 240, green);
  gdImageLine (im_out, 16, 240, 16, 16, green);
  /* Circle */
  gdImageArc (im_out, 128, 128, 60, 20, 0, 720, blue);
  /* Arc */
  gdImageArc (im_out, 128, 128, 40, 40, 90, 270, blue);
  /* Flood fill: doesn't do much on a continuously
     variable tone jpeg original. */
  gdImageFill (im_out, 8, 8, blue);
  /* Polygon */
  points[0].x = 64;
  points[0].y = 0;
  points[1].x = 0;
  points[1].y = 128;
  points[2].x = 128;
  points[2].y = 128;
  gdImageFilledPolygon (im_out, points, 3, green);
  /* Brush. A fairly wild example also involving a line style! */
  if (im_in)
    {
      int style[8];
      brush = gdImageCreateTrueColor (16, 16);
      gdImageCopyResized (brush, im_in,
			  0, 0, 0, 0,
			  gdImageSX (brush), gdImageSY (brush),
			  gdImageSX (im_in), gdImageSY (im_in));
      gdImageSetBrush (im_out, brush);
      /* With a style, so they won't overprint each other.
         Normally, they would, yielding a fat-brush effect. */
      style[0] = 0;
      style[1] = 0;
      style[2] = 0;
      style[3] = 0;
      style[4] = 0;
      style[5] = 0;
      style[6] = 0;
      style[7] = 1;
      gdImageSetStyle (im_out, style, 8);
      /* Draw the styled, brushed line */
      gdImageLine (im_out, 0, 255, 255, 0, gdStyledBrushed);
    }
  /* Text */
  gdImageString (im_out, gdFontGiant, 32, 32,
		 (unsigned char *) "hi", red);
  gdImageStringUp (im_out, gdFontSmall, 64, 64,
		   (unsigned char *) "hi", red);
  /* Make output image interlaced (progressive, in the case of JPEG) */
  gdImageInterlace (im_out, 1);
  out = fopen ("demoout.png", "wb");
  /* Write PNG */
  gdImagePng (im_out, out);
  fclose (out);
  gdImageDestroy (im_out);
  if (im_in)
    {
      gdImageDestroy (im_in);
    }
  return 0;
}