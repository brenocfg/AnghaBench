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
 int /*<<< orphan*/  gdImageGd2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  gdImagePaletteCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
main (int argc, char **argv)
{
  gdImagePtr im;
  gdImagePtr pal;
  FILE *in, *out;
  if (argc != 3)
    {
      fprintf (stderr, "Usage: gd2copypal palettefile.gd2 filename.gd2\n");
      exit (1);
    }
  in = fopen (argv[1], "rb");
  if (!in)
    {
      fprintf (stderr, "Palette file does not exist!\n");
      exit (1);
    }
  pal = gdImageCreateFromGd2 (in);
  fclose (in);
  if (!pal)
    {
      fprintf (stderr, "Palette is not in GD2 format!\n");
      exit (1);
    }

  in = fopen (argv[2], "rb");
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

  gdImagePaletteCopy (im, pal);

  out = fopen (argv[2], "wb");
  if (!out)
    {
      fprintf (stderr, "Output file cannot be written to!\n");
      gdImageDestroy (im);
      exit (1);
    }
  gdImageGd2 (im, out, 128, 2);
  fclose (out);
  gdImageDestroy (pal);
  gdImageDestroy (im);

  return 0;
}