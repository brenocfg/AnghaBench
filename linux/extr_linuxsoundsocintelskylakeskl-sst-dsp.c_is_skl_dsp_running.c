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
struct sst_dsp {scalar_t__ sst_state; } ;

/* Variables and functions */
 scalar_t__ SKL_DSP_RUNNING ; 

bool is_skl_dsp_running(struct sst_dsp *ctx)
{
	return (ctx->sst_state == SKL_DSP_RUNNING);
}