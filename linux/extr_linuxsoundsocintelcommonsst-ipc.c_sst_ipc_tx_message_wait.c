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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ (* check_dsp_lp_on ) (int /*<<< orphan*/ ,int) ;} ;
struct sst_generic_ipc {int /*<<< orphan*/  dsp; TYPE_1__ ops; } ;

/* Variables and functions */
 int EIO ; 
 int ipc_tx_message (struct sst_generic_ipc*,int /*<<< orphan*/ ,void*,size_t,void*,size_t,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 

int sst_ipc_tx_message_wait(struct sst_generic_ipc *ipc, u64 header,
	void *tx_data, size_t tx_bytes, void *rx_data, size_t rx_bytes)
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

	ret = ipc_tx_message(ipc, header, tx_data, tx_bytes,
		rx_data, rx_bytes, 1);

	if (ipc->ops.check_dsp_lp_on)
		if (ipc->ops.check_dsp_lp_on(ipc->dsp, false))
			return -EIO;

	return ret;
}