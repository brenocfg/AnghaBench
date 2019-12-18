#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int width; int height; int* bitmap; } ;
typedef  TYPE_1__ Wbmp ;

/* Variables and functions */
 int WBMP_BLACK ; 
 int WBMP_WHITE ; 
 int /*<<< orphan*/  gdFree (TYPE_1__*) ; 
 scalar_t__ gdMalloc (int) ; 
 void* getmbi (int (*) (void*),void*) ; 
 scalar_t__ overflow2 (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ safe_emalloc (size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skipheader (int (*) (void*),void*) ; 

int
readwbmp (int (*getin) (void *in), void *in, Wbmp ** return_wbmp)
{
  int row, col, byte, pel, pos;
  Wbmp *wbmp;

  if ((wbmp = (Wbmp *) gdMalloc (sizeof (Wbmp))) == NULL)
    return (-1);

  wbmp->type = getin (in);
  if (wbmp->type != 0)
    {
      gdFree (wbmp);
      return (-1);
    }

  if (skipheader (getin, in))
    {
      gdFree (wbmp);
      return (-1);
    }


  wbmp->width = getmbi (getin, in);
  if (wbmp->width == -1)
    {
      gdFree (wbmp);
      return (-1);
    }

  wbmp->height = getmbi (getin, in);
  if (wbmp->height == -1)
    {
      gdFree (wbmp);
      return (-1);
    }

#ifdef __DEBUG
  printf ("W: %d, H: %d\n", wbmp->width, wbmp->height);
#endif

  if (overflow2(sizeof (int), wbmp->width) ||
    overflow2(sizeof (int) * wbmp->width, wbmp->height))
    {
      gdFree(wbmp);
      return (-1);
    }

  if ((wbmp->bitmap = (int *) safe_emalloc((size_t)wbmp->width * wbmp->height, sizeof(int), 0)) == NULL)
    {
      gdFree (wbmp);
      return (-1);
    }

#ifdef __DEBUG
  printf ("DATA CONSTRUCTED\n");
#endif

  pos = 0;
  for (row = 0; row < wbmp->height; row++)
    {
      for (col = 0; col < wbmp->width;)
	{
	  byte = getin (in);

	  for (pel = 7; pel >= 0; pel--)
	    {
	      if (col++ < wbmp->width)
		{
		  if (byte & 1 << pel)
		    {
		      wbmp->bitmap[pos] = WBMP_WHITE;
		    }
		  else
		    {
		      wbmp->bitmap[pos] = WBMP_BLACK;
		    }
		  pos++;
		}
	    }
	}
    }

  *return_wbmp = wbmp;

  return (0);
}