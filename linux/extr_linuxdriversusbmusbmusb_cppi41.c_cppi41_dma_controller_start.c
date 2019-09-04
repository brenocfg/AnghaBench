#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct musb {struct device* controller; } ;
struct dma_channel {int /*<<< orphan*/  max_len; int /*<<< orphan*/  status; struct cppi41_dma_channel* private_data; } ;
struct dma_chan {int dummy; } ;
struct device_node {int dummy; } ;
struct device {TYPE_2__* parent; } ;
struct TYPE_3__ {struct musb* musb; } ;
struct cppi41_dma_controller {unsigned int num_channels; struct cppi41_dma_channel* rx_channel; struct cppi41_dma_channel* tx_channel; TYPE_1__ controller; } ;
struct cppi41_dma_channel {unsigned int port_num; unsigned int is_tx; struct dma_chan* dc; struct dma_channel channel; int /*<<< orphan*/  tx_check; struct cppi41_dma_controller* controller; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct dma_chan*) ; 
 int /*<<< orphan*/  MUSB_DMA_STATUS_FREE ; 
 int PTR_ERR (struct dma_chan*) ; 
 int /*<<< orphan*/  SZ_4M ; 
 int /*<<< orphan*/  cppi41_release_all_dma_chans (struct cppi41_dma_controller*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,...) ; 
 struct dma_chan* dma_request_chan (TYPE_2__*,char const*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 scalar_t__ strstarts (char const*,char*) ; 

__attribute__((used)) static int cppi41_dma_controller_start(struct cppi41_dma_controller *controller)
{
	struct musb *musb = controller->controller.musb;
	struct device *dev = musb->controller;
	struct device_node *np = dev->parent->of_node;
	struct cppi41_dma_channel *cppi41_channel;
	int count;
	int i;
	int ret;

	count = of_property_count_strings(np, "dma-names");
	if (count < 0)
		return count;

	for (i = 0; i < count; i++) {
		struct dma_chan *dc;
		struct dma_channel *musb_dma;
		const char *str;
		unsigned is_tx;
		unsigned int port;

		ret = of_property_read_string_index(np, "dma-names", i, &str);
		if (ret)
			goto err;
		if (strstarts(str, "tx"))
			is_tx = 1;
		else if (strstarts(str, "rx"))
			is_tx = 0;
		else {
			dev_err(dev, "Wrong dmatype %s\n", str);
			goto err;
		}
		ret = kstrtouint(str + 2, 0, &port);
		if (ret)
			goto err;

		ret = -EINVAL;
		if (port > controller->num_channels || !port)
			goto err;
		if (is_tx)
			cppi41_channel = &controller->tx_channel[port - 1];
		else
			cppi41_channel = &controller->rx_channel[port - 1];

		cppi41_channel->controller = controller;
		cppi41_channel->port_num = port;
		cppi41_channel->is_tx = is_tx;
		INIT_LIST_HEAD(&cppi41_channel->tx_check);

		musb_dma = &cppi41_channel->channel;
		musb_dma->private_data = cppi41_channel;
		musb_dma->status = MUSB_DMA_STATUS_FREE;
		musb_dma->max_len = SZ_4M;

		dc = dma_request_chan(dev->parent, str);
		if (IS_ERR(dc)) {
			ret = PTR_ERR(dc);
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to request %s: %d.\n",
					str, ret);
			goto err;
		}

		cppi41_channel->dc = dc;
	}
	return 0;
err:
	cppi41_release_all_dma_chans(controller);
	return ret;
}