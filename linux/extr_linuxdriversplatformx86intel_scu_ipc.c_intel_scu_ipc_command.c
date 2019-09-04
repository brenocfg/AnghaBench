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
struct intel_scu_ipc_dev {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int intel_scu_ipc_check_status (struct intel_scu_ipc_dev*) ; 
 int /*<<< orphan*/  ipc_command (struct intel_scu_ipc_dev*,int) ; 
 int /*<<< orphan*/  ipc_data_readl (struct intel_scu_ipc_dev*,int) ; 
 int /*<<< orphan*/  ipc_data_writel (struct intel_scu_ipc_dev*,int /*<<< orphan*/ ,int) ; 
 struct intel_scu_ipc_dev ipcdev ; 
 int /*<<< orphan*/  ipclock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_scu_ipc_command(int cmd, int sub, u32 *in, int inlen,
			  u32 *out, int outlen)
{
	struct intel_scu_ipc_dev *scu = &ipcdev;
	int i, err;

	mutex_lock(&ipclock);
	if (scu->dev == NULL) {
		mutex_unlock(&ipclock);
		return -ENODEV;
	}

	for (i = 0; i < inlen; i++)
		ipc_data_writel(scu, *in++, 4 * i);

	ipc_command(scu, (inlen << 16) | (sub << 12) | cmd);
	err = intel_scu_ipc_check_status(scu);

	if (!err) {
		for (i = 0; i < outlen; i++)
			*out++ = ipc_data_readl(scu, 4 * i);
	}

	mutex_unlock(&ipclock);
	return err;
}