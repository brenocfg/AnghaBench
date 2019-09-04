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

/* Variables and functions */
 float nvg__maxf (float,float) ; 
 float nvg__minf (float,float) ; 

__attribute__((used)) static void nvg__isectRects(float* dst,
							float ax, float ay, float aw, float ah,
							float bx, float by, float bw, float bh)
{
	float minx = nvg__maxf(ax, bx);
	float miny = nvg__maxf(ay, by);
	float maxx = nvg__minf(ax+aw, bx+bw);
	float maxy = nvg__minf(ay+ah, by+bh);
	dst[0] = minx;
	dst[1] = miny;
	dst[2] = nvg__maxf(0.0f, maxx - minx);
	dst[3] = nvg__maxf(0.0f, maxy - miny);
}