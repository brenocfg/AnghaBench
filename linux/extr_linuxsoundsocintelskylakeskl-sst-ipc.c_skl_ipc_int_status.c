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
 int SKL_ADSPIS_IPC ; 
 int /*<<< orphan*/  SKL_ADSP_REG_ADSPIS ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 

bool skl_ipc_int_status(struct sst_dsp *ctx)
{
	return sst_dsp_shim_read_unlocked(ctx,
			SKL_ADSP_REG_ADSPIS) & SKL_ADSPIS_IPC;
}