#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sst_dsp {struct skl_sst* thread_context; } ;
struct TYPE_2__ {int* usage_count; int count; int /*<<< orphan*/ * state; } ;
struct skl_sst {TYPE_1__ cores; } ;

/* Variables and functions */
 size_t SKL_DSP_CORE0_ID ; 
 int /*<<< orphan*/  SKL_DSP_RESET ; 
 int /*<<< orphan*/  SKL_DSP_RUNNING ; 

void skl_dsp_init_core_state(struct sst_dsp *ctx)
{
	struct skl_sst *skl = ctx->thread_context;
	int i;

	skl->cores.state[SKL_DSP_CORE0_ID] = SKL_DSP_RUNNING;
	skl->cores.usage_count[SKL_DSP_CORE0_ID] = 1;

	for (i = SKL_DSP_CORE0_ID + 1; i < skl->cores.count; i++) {
		skl->cores.state[i] = SKL_DSP_RESET;
		skl->cores.usage_count[i] = 0;
	}
}