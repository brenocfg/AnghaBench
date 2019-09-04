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
struct TYPE_3__ {int /*<<< orphan*/  xform; } ;
typedef  TYPE_1__ NVGstate ;

/* Variables and functions */
 int /*<<< orphan*/  nvg__getAverageScale (int /*<<< orphan*/ ) ; 
 float nvg__minf (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  nvg__quantize (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static float nvg__getFontScale(NVGstate* state)
{
	return nvg__minf(nvg__quantize(nvg__getAverageScale(state->xform), 0.01f), 4.0f);
}