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
struct TYPE_2__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_complete; scalar_t__ irq_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EACCES ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int IPC_CMD_SIZE ; 
 int IPC_ERR_EMSECURITY ; 
 int IPC_ERR_UNSIGNEDKERNEL ; 
 int IPC_LOOP_CNT ; 
 int IPC_MAX_SEC ; 
 int IPC_STATUS_BUSY ; 
 int IPC_STATUS_ERR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/ * ipc_err_sources ; 
 int ipc_read_status () ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int intel_pmc_ipc_check_status(void)
{
	int status;
	int ret = 0;

	if (ipcdev.irq_mode) {
		if (0 == wait_for_completion_timeout(
				&ipcdev.cmd_complete, IPC_MAX_SEC * HZ))
			ret = -ETIMEDOUT;
	} else {
		int loop_count = IPC_LOOP_CNT;

		while ((ipc_read_status() & IPC_STATUS_BUSY) && --loop_count)
			udelay(1);
		if (loop_count == 0)
			ret = -ETIMEDOUT;
	}

	status = ipc_read_status();
	if (ret == -ETIMEDOUT) {
		dev_err(ipcdev.dev,
			"IPC timed out, TS=0x%x, CMD=0x%x\n",
			status, ipcdev.cmd);
		return ret;
	}

	if (status & IPC_STATUS_ERR) {
		int i;

		ret = -EIO;
		i = (status >> IPC_CMD_SIZE) & 0xFF;
		if (i < ARRAY_SIZE(ipc_err_sources))
			dev_err(ipcdev.dev,
				"IPC failed: %s, STS=0x%x, CMD=0x%x\n",
				ipc_err_sources[i], status, ipcdev.cmd);
		else
			dev_err(ipcdev.dev,
				"IPC failed: unknown, STS=0x%x, CMD=0x%x\n",
				status, ipcdev.cmd);
		if ((i == IPC_ERR_UNSIGNEDKERNEL) || (i == IPC_ERR_EMSECURITY))
			ret = -EACCES;
	}

	return ret;
}