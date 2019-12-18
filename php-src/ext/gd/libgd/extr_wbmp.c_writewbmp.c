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
struct TYPE_3__ {int width; int height; int* bitmap; } ;
typedef  TYPE_1__ Wbmp ;

/* Variables and functions */
 int WBMP_BLACK ; 
 int WBMP_WHITE ; 
 int /*<<< orphan*/  putmbi (int,void (*) (int,void*),void*) ; 

int
writewbmp (Wbmp * wbmp, void (*putout) (int c, void *out), void *out)
{
  int row, col;
  int bitpos, octet;

  /* Generate the header */
  putout (0, out);		/* WBMP Type 0: B/W, Uncompressed bitmap */
  putout (0, out);		/* FixHeaderField */



  /* Size of the image */
  putmbi (wbmp->width, putout, out);	/* width */
  putmbi (wbmp->height, putout, out);	/* height */


  /* Image data */
  for (row = 0; row < wbmp->height; row++)
    {
      bitpos = 8;
      octet = 0;
      for (col = 0; col < wbmp->width; col++)
	{
	  octet |= ((wbmp->bitmap[row * wbmp->width + col] == 1) ? WBMP_WHITE : WBMP_BLACK) << --bitpos;
	  if (bitpos == 0)
	    {
	      bitpos = 8;
	      putout (octet, out);
	      octet = 0;
	    }
	}
      if (bitpos != 8)
	putout (octet, out);

    }
  return (0);

}