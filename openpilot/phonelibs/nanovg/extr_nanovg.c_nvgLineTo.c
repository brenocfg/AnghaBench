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
 int /*<<< orphan*/  NVG_COUNTOF (float*) ; 
 float NVG_LINETO ; 
 int /*<<< orphan*/  nvg__appendCommands (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ) ; 

void nvgLineTo(NVGcontext* ctx, float x, float y)
{
	float vals[] = { NVG_LINETO, x, y };
	nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}