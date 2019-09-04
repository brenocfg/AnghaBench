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
struct TYPE_3__ {int* style; int styleLength; scalar_t__ stylePos; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdFree (int*) ; 
 scalar_t__ gdMalloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ overflow2 (int,int) ; 

void gdImageSetStyle (gdImagePtr im, int *style, int noOfPixels)
{
	if (im->style) {
		gdFree(im->style);
	}
	if (overflow2(sizeof (int), noOfPixels)) {
		return;
	}
	im->style = (int *) gdMalloc(sizeof(int) * noOfPixels);
	memcpy(im->style, style, sizeof(int) * noOfPixels);
	im->styleLength = noOfPixels;
	im->stylePos = 0;
}