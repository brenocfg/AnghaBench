#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int srcRGB; int dstRGB; int srcAlpha; int dstAlpha; } ;
struct TYPE_4__ {TYPE_2__ compositeOperation; } ;
typedef  TYPE_1__ NVGstate ;
typedef  int /*<<< orphan*/  NVGcontext ;
typedef  TYPE_2__ NVGcompositeOperationState ;

/* Variables and functions */
 TYPE_1__* nvg__getState (int /*<<< orphan*/ *) ; 

void nvgGlobalCompositeBlendFuncSeparate(NVGcontext* ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)
{
	NVGcompositeOperationState op;
	op.srcRGB = srcRGB;
	op.dstRGB = dstRGB;
	op.srcAlpha = srcAlpha;
	op.dstAlpha = dstAlpha;

	NVGstate* state = nvg__getState(ctx);
	state->compositeOperation = op;
}