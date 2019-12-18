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
struct TYPE_2__ {int (* set_state_D0i0 ) (struct sst_dsp*) ;int (* set_state_D0i3 ) (struct sst_dsp*) ;} ;
struct sst_dsp {TYPE_1__ fw_ops; } ;

/* Variables and functions */
 int stub1 (struct sst_dsp*) ; 
 int stub2 (struct sst_dsp*) ; 

int skl_ipc_check_D0i0(struct sst_dsp *dsp, bool state)
{
	int ret;

	/* check D0i3 support */
	if (!dsp->fw_ops.set_state_D0i0)
		return 0;

	/* Attempt D0i0 or D0i3 based on state */
	if (state)
		ret = dsp->fw_ops.set_state_D0i0(dsp);
	else
		ret = dsp->fw_ops.set_state_D0i3(dsp);

	return ret;
}