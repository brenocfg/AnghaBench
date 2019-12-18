#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imx_dsp_ipc {int dummy; } ;
struct imx8_priv {TYPE_1__* sdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx8_get_reply (TYPE_1__*) ; 
 struct imx8_priv* imx_dsp_get_data (struct imx_dsp_ipc*) ; 
 int /*<<< orphan*/  snd_sof_ipc_reply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imx8_dsp_handle_reply(struct imx_dsp_ipc *ipc)
{
	struct imx8_priv *priv = imx_dsp_get_data(ipc);
	unsigned long flags;

	spin_lock_irqsave(&priv->sdev->ipc_lock, flags);
	imx8_get_reply(priv->sdev);
	snd_sof_ipc_reply(priv->sdev, 0);
	spin_unlock_irqrestore(&priv->sdev->ipc_lock, flags);
}