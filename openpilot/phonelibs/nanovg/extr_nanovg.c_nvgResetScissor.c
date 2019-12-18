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
struct TYPE_4__ {float* extent; int /*<<< orphan*/  xform; } ;
struct TYPE_5__ {TYPE_1__ scissor; } ;
typedef  TYPE_2__ NVGstate ;
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* nvg__getState (int /*<<< orphan*/ *) ; 

void nvgResetScissor(NVGcontext* ctx)
{
	NVGstate* state = nvg__getState(ctx);
	memset(state->scissor.xform, 0, sizeof(state->scissor.xform));
	state->scissor.extent[0] = -1.0f;
	state->scissor.extent[1] = -1.0f;
}