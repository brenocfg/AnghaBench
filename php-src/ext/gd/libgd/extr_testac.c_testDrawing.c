#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gdImagePtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  gdImageAlphaBlending (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdImageCopyResampled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,double,double) ; 
 int /*<<< orphan*/  gdImageCreateTrueColor (int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageFill (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImagePng (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double gdImageSX (int /*<<< orphan*/ ) ; 
 double gdImageSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageSaveAlpha (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdImageTrueColorToPalette (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gdTrueColor (int,int,int) ; 

void
testDrawing (
	      gdImagePtr im_in,
	      double scale,
	      int blending,
	      int palette,
	      char *filename)
{
  gdImagePtr im_out;
  FILE *out;
  /* Create output image. */
  im_out = gdImageCreateTrueColor ((int) (gdImageSX (im_in) * scale),
				   (int) (gdImageSY (im_in) * scale));
  /*
     Request alpha blending. This causes future
     drawing operations to perform alpha channel blending
     with the background, resulting in an opaque image.
     Without this call, pixels in the foreground color are
     copied literally, *including* the alpha channel value,
     resulting in an output image which is potentially
     not opaque. This flag can be set and cleared as often
     as desired. */
  gdImageAlphaBlending (im_out, blending);

  /* Flood with light blue. */
  gdImageFill (im_out, (int) (gdImageSX (im_in) * scale / 2),
	       (int) (gdImageSY (im_in) * scale / 2),
	       gdTrueColor (192, 192, 255));
  /* Copy the source image. Alpha blending should result in
     compositing against red. With blending turned off, the
     browser or viewer will composite against its preferred
     background, or, if it does not support an alpha channel,
     we will see the original colors for the pixels that
     ought to be transparent or semitransparent. */
  gdImageCopyResampled (im_out, im_in,
			0, 0,
			0, 0,
       (int) (gdImageSX (im_in) * scale), (int) (gdImageSY (im_in) * scale),
			gdImageSX (im_in), gdImageSY (im_in));
  /* Write PNG */
  out = fopen (filename, "wb");

  /* If this image is the result of alpha channel blending,
     it will not contain an interesting alpha channel itself.
     Save a little file size by not saving the alpha channel.
     Otherwise the file would typically be slightly larger. */
  gdImageSaveAlpha (im_out, !blending);

  /* If requested, convert from truecolor to palette. */
  if (palette)
    {
      /* Dithering, 256 colors. */
      gdImageTrueColorToPalette (im_out, 1, 256);
    }

  gdImagePng (im_out, out);
  fclose (out);

  gdImageDestroy (im_out);
}