#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdImagePtr ;
struct TYPE_6__ {int colorsTotal; } ;

/* Variables and functions */
 int GD_CMP_COLOR ; 
 int GD_CMP_IMAGE ; 
 int GD_CMP_NUM_COLORS ; 
 int GD_CMP_SIZE_X ; 
 int GD_CMP_SIZE_Y ; 
 int gdImageCompare (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

void
CompareImages (char *msg, gdImagePtr im1, gdImagePtr im2)
{
  int cmpRes;

  cmpRes = gdImageCompare (im1, im2);

  if (cmpRes & GD_CMP_IMAGE)
    {
      printf ("%%%s: ERROR images differ: BAD\n", msg);
    }
  else if (cmpRes != 0)
    {
      printf ("%%%s: WARNING images differ: WARNING - Probably OK\n", msg);
    }
  else
    {
      printf ("%%%s: OK\n", msg);
      return;
    }

  if (cmpRes & (GD_CMP_SIZE_X + GD_CMP_SIZE_Y))
    {
      printf ("-%s: INFO image sizes differ\n", msg);
    }

  if (cmpRes & GD_CMP_NUM_COLORS)
    {
      printf ("-%s: INFO number of pallette entries differ %d Vs. %d\n", msg,
	      im1->colorsTotal, im2->colorsTotal);
    }

  if (cmpRes & GD_CMP_COLOR)
    {
      printf ("-%s: INFO actual colours of pixels differ\n", msg);
    }
}