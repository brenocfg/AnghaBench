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
struct TYPE_4__ {float x; float dy; float y; float dx; float dmx; float dmy; } ;
typedef  TYPE_1__ NVGpoint ;

/* Variables and functions */

__attribute__((used)) static void nvg__chooseBevel(int bevel, NVGpoint* p0, NVGpoint* p1, float w,
							float* x0, float* y0, float* x1, float* y1)
{
	if (bevel) {
		*x0 = p1->x + p0->dy * w;
		*y0 = p1->y - p0->dx * w;
		*x1 = p1->x + p1->dy * w;
		*y1 = p1->y - p1->dx * w;
	} else {
		*x0 = p1->x + p1->dmx * w;
		*y0 = p1->y + p1->dmy * w;
		*x1 = p1->x + p1->dmx * w;
		*y1 = p1->y + p1->dmy * w;
	}
}