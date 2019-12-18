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
 int /*<<< orphan*/  nvgGlobalCompositeBlendFuncSeparate (int /*<<< orphan*/ *,int,int,int,int) ; 

void nvgGlobalCompositeBlendFunc(NVGcontext* ctx, int sfactor, int dfactor)
{
	nvgGlobalCompositeBlendFuncSeparate(ctx, sfactor, dfactor, sfactor, dfactor);
}