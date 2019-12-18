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
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdImageCreateFromGd2Part (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImagePng (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int
main (int argc, char **argv)
{
  gdImagePtr im;
  FILE *in, *out;
  int x, y, w, h;

  if (argc != 7)
    {
      fprintf (stderr, "Usage: gdparttopng filename.gd filename.png x y w h\n");
      exit (1);
    }
  in = fopen (argv[1], "rb");
  if (!in)
    {
      fprintf (stderr, "Input file does not exist!\n");
      exit (1);
    }

  x = atoi (argv[3]);
  y = atoi (argv[4]);
  w = atoi (argv[5]);
  h = atoi (argv[6]);

  printf ("Extracting from (%d, %d), size is %dx%d\n", x, y, w, h);

  im = gdImageCreateFromGd2Part (in, x, y, w, h);
  fclose (in);
  if (!im)
    {
      fprintf (stderr, "Input is not in GD2 format!\n");
      exit (1);
    }
  out = fopen (argv[2], "wb");
  if (!out)
    {
      fprintf (stderr, "Output file cannot be written to!\n");
      gdImageDestroy (im);
      exit (1);
    }
#ifdef HAVE_LIBPNG
  gdImagePng (im, out);
#else
  fprintf(stderr, "No PNG library support.\n");
#endif
  fclose (out);
  gdImageDestroy (im);

  return 0;
}