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
 int /*<<< orphan*/  gdImageCreateFromPng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdImageDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdImageGd2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int
main (int argc, char **argv)
{
  gdImagePtr im;
  FILE *in, *out;
  int cs, fmt;

  if (argc != 5)
    {
      fprintf (stderr, "Usage: pngtogd2 filename.png filename.gd2 cs fmt\n");
      fprintf (stderr, "    where cs is the chunk size\n");
      fprintf (stderr, "          fmt is 1 for raw, 2 for compressed\n");
      exit (1);
    }
  in = fopen (argv[1], "rb");
  if (!in)
    {
      fprintf (stderr, "Input file does not exist!\n");
      exit (1);
    }
  im = gdImageCreateFromPng (in);
  fclose (in);
  if (!im)
    {
      fprintf (stderr, "Input is not in PNG format!\n");
      exit (1);
    }
  out = fopen (argv[2], "wb");
  if (!out)
    {
      fprintf (stderr, "Output file cannot be written to!\n");
      gdImageDestroy (im);
      exit (1);
    }
  cs = atoi (argv[3]);
  fmt = atoi (argv[4]);
  gdImageGd2 (im, out, cs, fmt);
  fclose (out);
  gdImageDestroy (im);

  return 0;
}