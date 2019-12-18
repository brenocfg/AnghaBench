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
struct sst_dsp {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_DSP_CORE0_MASK ; 
 int /*<<< orphan*/  cnl_dsp_disable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_ipc_int_disable (struct sst_dsp*) ; 
 int /*<<< orphan*/  cnl_ipc_op_int_disable (struct sst_dsp*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sst_dsp*) ; 

void cnl_dsp_free(struct sst_dsp *dsp)
{
	cnl_ipc_int_disable(dsp);

	free_irq(dsp->irq, dsp);
	cnl_ipc_op_int_disable(dsp);
	cnl_dsp_disable_core(dsp, SKL_DSP_CORE0_MASK);
}