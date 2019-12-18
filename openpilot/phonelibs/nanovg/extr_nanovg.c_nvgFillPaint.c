#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  xform; } ;
struct TYPE_5__ {int /*<<< orphan*/  xform; TYPE_2__ fill; } ;
typedef  TYPE_1__ NVGstate ;
typedef  TYPE_2__ NVGpaint ;
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  nvgTransformMultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* nvg__getState (int /*<<< orphan*/ *) ; 

void nvgFillPaint(NVGcontext* ctx, NVGpaint paint)
{
	NVGstate* state = nvg__getState(ctx);
	state->fill = paint;
	nvgTransformMultiply(state->fill.xform, state->xform);
}