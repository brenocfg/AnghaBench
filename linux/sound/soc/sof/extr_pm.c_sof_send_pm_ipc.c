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
struct sof_ipc_reply {int dummy; } ;
struct TYPE_2__ {int size; int cmd; } ;
struct sof_ipc_pm_ctx {TYPE_1__ hdr; } ;
struct snd_sof_dev {int /*<<< orphan*/  ipc; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  pm_ctx ;

/* Variables and functions */
 int SOF_IPC_GLB_PM_MSG ; 
 int /*<<< orphan*/  memset (struct sof_ipc_pm_ctx*,int /*<<< orphan*/ ,int) ; 
 int sof_ipc_tx_message (int /*<<< orphan*/ ,int,struct sof_ipc_pm_ctx*,int,struct sof_ipc_reply*,int) ; 

__attribute__((used)) static int sof_send_pm_ipc(struct snd_sof_dev *sdev, int cmd)
{
	struct sof_ipc_pm_ctx pm_ctx;
	struct sof_ipc_reply reply;

	memset(&pm_ctx, 0, sizeof(pm_ctx));

	/* configure ctx save ipc message */
	pm_ctx.hdr.size = sizeof(pm_ctx);
	pm_ctx.hdr.cmd = SOF_IPC_GLB_PM_MSG | cmd;

	/* send ctx save ipc to dsp */
	return sof_ipc_tx_message(sdev->ipc, pm_ctx.hdr.cmd, &pm_ctx,
				 sizeof(pm_ctx), &reply, sizeof(reply));
}