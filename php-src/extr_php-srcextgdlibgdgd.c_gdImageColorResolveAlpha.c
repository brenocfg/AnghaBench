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
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_3__ {int colorsTotal; int transparent; int* red; int* green; int* blue; int* alpha; scalar_t__* open; scalar_t__ trueColor; } ;

/* Variables and functions */
 int gdMaxColors ; 
 int gdTrueColorAlpha (int,int,int,int) ; 

int gdImageColorResolveAlpha (gdImagePtr im, int r, int g, int b, int a)
{
  int c;
  int ct = -1;
  int op = -1;
  long rd, gd, bd, ad, dist;
  long mindist = 4 * 255 * 255;	/* init to max poss dist */
  if (im->trueColor)
    {
      return gdTrueColorAlpha (r, g, b, a);
    }

  for (c = 0; c < im->colorsTotal; c++)
    {
      if (im->open[c])
	{
	  op = c;		/* Save open slot */
	  continue;		/* Color not in use */
	}
      if (c == im->transparent)
        {
          /* don't ever resolve to the color that has
           * been designated as the transparent color */
          continue;
	}
      rd = (long) (im->red[c] - r);
      gd = (long) (im->green[c] - g);
      bd = (long) (im->blue[c] - b);
      ad = (long) (im->alpha[c] - a);
      dist = rd * rd + gd * gd + bd * bd + ad * ad;
      if (dist < mindist)
	{
	  if (dist == 0)
	    {
	      return c;		/* Return exact match color */
	    }
	  mindist = dist;
	  ct = c;
	}
    }
  /* no exact match.  We now know closest, but first try to allocate exact */
  if (op == -1)
    {
      op = im->colorsTotal;
      if (op == gdMaxColors)
	{			/* No room for more colors */
	  return ct;		/* Return closest available color */
	}
      im->colorsTotal++;
    }
  im->red[op] = r;
  im->green[op] = g;
  im->blue[op] = b;
  im->alpha[op] = a;
  im->open[op] = 0;
  return op;			/* Return newly allocated color */
}