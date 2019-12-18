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
struct snd_sof_dev {scalar_t__ private; } ;
struct imx8_priv {int num_domains; int /*<<< orphan*/ * pd_dev; int /*<<< orphan*/ * link; int /*<<< orphan*/  ipc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_pm_domain_detach (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_link_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx8_remove(struct snd_sof_dev *sdev)
{
	struct imx8_priv *priv = (struct imx8_priv *)sdev->private;
	int i;

	platform_device_unregister(priv->ipc_dev);

	for (i = 0; i < priv->num_domains; i++) {
		device_link_del(priv->link[i]);
		dev_pm_domain_detach(priv->pd_dev[i], false);
	}

	return 0;
}