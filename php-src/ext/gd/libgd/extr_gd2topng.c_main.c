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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdImageCreateFromGd2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImagePng (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
main (int argc, char **argv)
{
  gdImagePtr im;
  FILE *in, *out;
  if (argc != 3)
    {
      fprintf (stderr, "Usage: gd2topng filename.gd2 filename.png\n");
      exit (1);
    }
  in = fopen (argv[1], "rb");
  if (!in)
    {
      fprintf (stderr, "Input file does not exist!\n");
      exit (1);
    }
  im = gdImageCreateFromGd2 (in);
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
  fprintf(stderr, "No PNG library support available.\n");
#endif
  fclose (out);
  gdImageDestroy (im);

  return 0;
}