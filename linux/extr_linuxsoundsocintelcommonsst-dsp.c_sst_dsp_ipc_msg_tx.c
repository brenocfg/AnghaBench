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
typedef  int u32 ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_IPCX ; 
 int SST_IPCX_BUSY ; 
 int /*<<< orphan*/  sst_dsp_shim_write_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_sst_ipc_msg_tx (int) ; 

void sst_dsp_ipc_msg_tx(struct sst_dsp *dsp, u32 msg)
{
	sst_dsp_shim_write_unlocked(dsp, SST_IPCX, msg | SST_IPCX_BUSY);
	trace_sst_ipc_msg_tx(msg);
}