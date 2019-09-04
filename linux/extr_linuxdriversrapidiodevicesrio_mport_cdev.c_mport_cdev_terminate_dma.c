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
struct mport_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void mport_cdev_terminate_dma(struct mport_dev *md)
{
#ifdef CONFIG_RAPIDIO_DMA_ENGINE
	struct mport_cdev_priv *client;

	rmcd_debug(DMA, "%s", dev_name(&md->dev));

	mutex_lock(&md->file_mutex);
	list_for_each_entry(client, &md->file_list, list) {
		if (client->dmach) {
			dmaengine_terminate_all(client->dmach);
			rio_release_dma(client->dmach);
		}
	}
	mutex_unlock(&md->file_mutex);

	if (md->dma_chan) {
		dmaengine_terminate_all(md->dma_chan);
		rio_release_dma(md->dma_chan);
		md->dma_chan = NULL;
	}
#endif
}