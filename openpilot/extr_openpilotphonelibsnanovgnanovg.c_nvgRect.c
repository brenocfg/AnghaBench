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
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 float NVG_CLOSE ; 
 int /*<<< orphan*/  NVG_COUNTOF (float*) ; 
 float NVG_LINETO ; 
 float NVG_MOVETO ; 
 int /*<<< orphan*/  nvg__appendCommands (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ) ; 

void nvgRect(NVGcontext* ctx, float x, float y, float w, float h)
{
	float vals[] = {
		NVG_MOVETO, x,y,
		NVG_LINETO, x,y+h,
		NVG_LINETO, x+w,y+h,
		NVG_LINETO, x+w,y,
		NVG_CLOSE
	};
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}