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
struct snd_sof_ipc_msg {int /*<<< orphan*/  msg_size; int /*<<< orphan*/  msg_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct snd_sof_dev {TYPE_1__ host_box; scalar_t__ private; } ;
struct imx8_priv {int /*<<< orphan*/  dsp_ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_dsp_ring_doorbell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sof_mailbox_write (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx8_send_msg(struct snd_sof_dev *sdev, struct snd_sof_ipc_msg *msg)
{
	struct imx8_priv *priv = (struct imx8_priv *)sdev->private;

	sof_mailbox_write(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	imx_dsp_ring_doorbell(priv->dsp_ipc, 0);

	return 0;
}