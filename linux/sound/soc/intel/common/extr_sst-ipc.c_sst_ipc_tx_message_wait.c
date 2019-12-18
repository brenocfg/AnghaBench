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
struct sst_ipc_message {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* check_dsp_lp_on ) (int /*<<< orphan*/ ,int) ;} ;
struct sst_generic_ipc {int /*<<< orphan*/  dsp; TYPE_1__ ops; } ;

/* Variables and functions */
 int EIO ; 
 int ipc_tx_message (struct sst_generic_ipc*,struct sst_ipc_message,struct sst_ipc_message*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 

int sst_ipc_tx_message_wait(struct sst_generic_ipc *ipc,
	struct sst_ipc_message request, struct sst_ipc_message *reply)
{
	int ret;

	/*
	 * DSP maybe in lower power active state, so
	 * check if the DSP supports DSP lp On method
	 * if so invoke that before sending IPC
	 */
	if (ipc->ops.check_dsp_lp_on)
		if (ipc->ops.check_dsp_lp_on(ipc->dsp, true))
			return -EIO;

	ret = ipc_tx_message(ipc, request, reply, 1);

	if (ipc->ops.check_dsp_lp_on)
		if (ipc->ops.check_dsp_lp_on(ipc->dsp, false))
			return -EIO;

	return ret;
}