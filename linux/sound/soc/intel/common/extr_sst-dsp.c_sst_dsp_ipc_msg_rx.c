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
typedef  int /*<<< orphan*/  u32 ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_IPCX ; 
 int /*<<< orphan*/  sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sst_ipc_msg_rx (int /*<<< orphan*/ ) ; 

u32 sst_dsp_ipc_msg_rx(struct sst_dsp *dsp)
{
	u32 msg;

	msg = sst_dsp_shim_read_unlocked(dsp, SST_IPCX);
	trace_sst_ipc_msg_rx(msg);

	return msg;
}