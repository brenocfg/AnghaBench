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
struct TYPE_3__ {int cx1; int cy1; int cx2; int cy2; } ;

/* Variables and functions */

void gdImageGetClip (gdImagePtr im, int *x1P, int *y1P, int *x2P, int *y2P)
{
	*x1P = im->cx1;
	*y1P = im->cy1;
	*x2P = im->cx2;
	*y2P = im->cy2;
}