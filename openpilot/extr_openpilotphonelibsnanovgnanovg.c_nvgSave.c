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
struct TYPE_3__ {size_t nstates; int /*<<< orphan*/ * states; } ;
typedef  int /*<<< orphan*/  NVGstate ;
typedef  TYPE_1__ NVGcontext ;

/* Variables and functions */
 size_t NVG_MAX_STATES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void nvgSave(NVGcontext* ctx)
{
	if (ctx->nstates >= NVG_MAX_STATES)
		return;
	if (ctx->nstates > 0)
		memcpy(&ctx->states[ctx->nstates], &ctx->states[ctx->nstates-1], sizeof(NVGstate));
	ctx->nstates++;
}