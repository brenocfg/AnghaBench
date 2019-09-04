#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_complete; } ;
typedef  int IPC_TYPE ;
typedef  TYPE_1__ IPC_DEV ;

/* Variables and functions */
 int CMD_PARA1_SHIFT ; 
 int CMD_PARA2_SHIFT ; 
 int CMD_RUN ; 
 int GTDRIVER_IPC ; 
 int IPC_PUNIT_CMD_TYPE_MASK ; 
 int IPC_TYPE_OFFSET ; 
 int ISPDRIVER_IPC ; 
 int intel_punit_ipc_check_status (TYPE_1__*,int) ; 
 int ipc_read_data_high (TYPE_1__*,int) ; 
 int ipc_read_data_low (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ipc_write_cmd (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ipc_write_data_high (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ipc_write_data_low (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* punit_ipcdev ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

int intel_punit_ipc_command(u32 cmd, u32 para1, u32 para2, u32 *in, u32 *out)
{
	IPC_DEV *ipcdev = punit_ipcdev;
	IPC_TYPE type;
	u32 val;
	int ret;

	mutex_lock(&ipcdev->lock);

	reinit_completion(&ipcdev->cmd_complete);
	type = (cmd & IPC_PUNIT_CMD_TYPE_MASK) >> IPC_TYPE_OFFSET;

	if (in) {
		ipc_write_data_low(ipcdev, type, *in);
		if (type == GTDRIVER_IPC || type == ISPDRIVER_IPC)
			ipc_write_data_high(ipcdev, type, *++in);
	}

	val = cmd & ~IPC_PUNIT_CMD_TYPE_MASK;
	val |= CMD_RUN | para2 << CMD_PARA2_SHIFT | para1 << CMD_PARA1_SHIFT;
	ipc_write_cmd(ipcdev, type, val);

	ret = intel_punit_ipc_check_status(ipcdev, type);
	if (ret)
		goto out;

	if (out) {
		*out = ipc_read_data_low(ipcdev, type);
		if (type == GTDRIVER_IPC || type == ISPDRIVER_IPC)
			*++out = ipc_read_data_high(ipcdev, type);
	}

out:
	mutex_unlock(&ipcdev->lock);
	return ret;
}