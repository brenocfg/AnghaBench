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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdImageCreateFromPng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  testDrawing (int /*<<< orphan*/ ,double,int,int,char*) ; 

int
main (int argc, char *argv[])
{
  /* Input and output files */
  FILE *in;
  FILE *out;

  /* Input image */
  gdImagePtr im_in = 0;

  /* Colors */
  int lightBlue;

  if (argc != 2)
    {
      fprintf (stderr, "Usage: testac filename.png\n");
      exit (1);
    }
  /* Load original PNG, which should contain alpha channel
     information. We will use it in two ways: preserving it
     literally, for use with compatible browsers, and
     compositing it ourselves against a background of our
     choosing (alpha blending). We'll change its size
     and try creating palette versions of it. */
  in = fopen (argv[1], "rb");
  if (!in)
    {
      fprintf (stderr, "Can't load %s.\n", argv[1]);
      exit (1);
    }
  else
    {
      im_in = gdImageCreateFromPng (in);
      fclose (in);
    }
  testDrawing (im_in, 1.0, 0, 0, "noblending-fullsize-truecolor.png");
  testDrawing (im_in, 1.0, 1, 0, "blending-fullsize-truecolor.png");
  testDrawing (im_in, 0.5, 0, 0, "noblending-halfsize-truecolor.png");
  testDrawing (im_in, 0.5, 1, 0, "blending-halfsize-truecolor.png");
  testDrawing (im_in, 2.0, 0, 0, "noblending-doublesize-truecolor.png");
  testDrawing (im_in, 2.0, 1, 0, "blending-doublesize-truecolor.png");
  testDrawing (im_in, 1.0, 0, 1, "noblending-fullsize-palette.png");
  testDrawing (im_in, 1.0, 1, 1, "blending-fullsize-palette.png");
  testDrawing (im_in, 0.5, 0, 1, "noblending-halfsize-palette.png");
  testDrawing (im_in, 0.5, 1, 1, "blending-halfsize-palette.png");
  testDrawing (im_in, 2.0, 0, 1, "noblending-doublesize-palette.png");
  testDrawing (im_in, 2.0, 1, 1, "blending-doublesize-palette.png");
  gdImageDestroy (im_in);
  return 0;
}