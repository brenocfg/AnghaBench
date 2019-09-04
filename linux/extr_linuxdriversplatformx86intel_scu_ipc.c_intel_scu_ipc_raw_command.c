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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_scu_ipc_dev {scalar_t__ ipc_base; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IPC_DPTR ; 
 scalar_t__ IPC_SPTR ; 
 int intel_scu_ipc_check_status (struct intel_scu_ipc_dev*) ; 
 int /*<<< orphan*/  ipc_command (struct intel_scu_ipc_dev*,int) ; 
 int /*<<< orphan*/  ipc_data_readl (struct intel_scu_ipc_dev*,int) ; 
 int /*<<< orphan*/  ipc_data_writel (struct intel_scu_ipc_dev*,int /*<<< orphan*/ ,int) ; 
 struct intel_scu_ipc_dev ipcdev ; 
 int /*<<< orphan*/  ipclock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int intel_scu_ipc_raw_command(int cmd, int sub, u8 *in, int inlen,
			      u32 *out, int outlen, u32 dptr, u32 sptr)
{
	struct intel_scu_ipc_dev *scu = &ipcdev;
	int inbuflen = DIV_ROUND_UP(inlen, 4);
	u32 inbuf[4];
	int i, err;

	/* Up to 16 bytes */
	if (inbuflen > 4)
		return -EINVAL;

	mutex_lock(&ipclock);
	if (scu->dev == NULL) {
		mutex_unlock(&ipclock);
		return -ENODEV;
	}

	writel(dptr, scu->ipc_base + IPC_DPTR);
	writel(sptr, scu->ipc_base + IPC_SPTR);

	/*
	 * SRAM controller doesn't support 8-bit writes, it only
	 * supports 32-bit writes, so we have to copy input data into
	 * the temporary buffer, and SCU FW will use the inlen to
	 * determine the actual input data length in the temporary
	 * buffer.
	 */
	memcpy(inbuf, in, inlen);

	for (i = 0; i < inbuflen; i++)
		ipc_data_writel(scu, inbuf[i], 4 * i);

	ipc_command(scu, (inlen << 16) | (sub << 12) | cmd);
	err = intel_scu_ipc_check_status(scu);
	if (!err) {
		for (i = 0; i < outlen; i++)
			*out++ = ipc_data_readl(scu, 4 * i);
	}

	mutex_unlock(&ipclock);
	return err;
}