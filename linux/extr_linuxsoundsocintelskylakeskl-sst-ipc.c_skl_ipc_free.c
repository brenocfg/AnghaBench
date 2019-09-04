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
struct sst_generic_ipc {int /*<<< orphan*/  dsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCCTL_BUSY ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_ipc_fini (struct sst_generic_ipc*) ; 

void skl_ipc_free(struct sst_generic_ipc *ipc)
{
	/* Disable IPC DONE interrupt */
	sst_dsp_shim_update_bits(ipc->dsp, SKL_ADSP_REG_HIPCCTL,
		SKL_ADSP_REG_HIPCCTL_DONE, 0);

	/* Disable IPC BUSY interrupt */
	sst_dsp_shim_update_bits(ipc->dsp, SKL_ADSP_REG_HIPCCTL,
		SKL_ADSP_REG_HIPCCTL_BUSY, 0);

	sst_ipc_fini(ipc);
}