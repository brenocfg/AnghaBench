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
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_DSP_CORE0_ID ; 
 int skl_dsp_get_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 

int skl_dsp_wake(struct sst_dsp *ctx)
{
	return skl_dsp_get_core(ctx, SKL_DSP_CORE0_ID);
}