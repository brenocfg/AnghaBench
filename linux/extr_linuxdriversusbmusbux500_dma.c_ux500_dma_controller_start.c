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
typedef  int u8 ;
typedef  size_t u32 ;
struct ux500_musb_board_data {void** dma_rx_param_array; void** dma_tx_param_array; int /*<<< orphan*/ * dma_filter; } ;
struct ux500_dma_controller {struct ux500_dma_channel* tx_channel; struct ux500_dma_channel* rx_channel; struct musb* private_data; } ;
struct dma_channel {int /*<<< orphan*/  max_len; int /*<<< orphan*/  status; struct ux500_dma_channel* private_data; } ;
struct ux500_dma_channel {size_t ch_num; int is_tx; scalar_t__ dma_chan; struct dma_channel channel; struct ux500_dma_controller* controller; } ;
struct musb_hdrc_platform_data {struct ux500_musb_board_data* board_data; } ;
struct musb {struct device* controller; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ERR (char*,int,size_t) ; 
 int /*<<< orphan*/  MUSB_DMA_STATUS_FREE ; 
 int /*<<< orphan*/  SZ_16M ; 
 size_t UX500_MUSB_DMA_NUM_RX_TX_CHANNELS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct musb_hdrc_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ dma_request_slave_channel (struct device*,char*) ; 
 scalar_t__ iep_chan_names ; 
 scalar_t__ oep_chan_names ; 
 int /*<<< orphan*/  ux500_dma_controller_stop (struct ux500_dma_controller*) ; 

__attribute__((used)) static int ux500_dma_controller_start(struct ux500_dma_controller *controller)
{
	struct ux500_dma_channel *ux500_channel = NULL;
	struct musb *musb = controller->private_data;
	struct device *dev = musb->controller;
	struct musb_hdrc_platform_data *plat = dev_get_platdata(dev);
	struct ux500_musb_board_data *data;
	struct dma_channel *dma_channel = NULL;
	char **chan_names;
	u32 ch_num;
	u8 dir;
	u8 is_tx = 0;

	void **param_array;
	struct ux500_dma_channel *channel_array;
	dma_cap_mask_t mask;

	if (!plat) {
		dev_err(musb->controller, "No platform data\n");
		return -EINVAL;
	}

	data = plat->board_data;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Prepare the loop for RX channels */
	channel_array = controller->rx_channel;
	param_array = data ? data->dma_rx_param_array : NULL;
	chan_names = (char **)iep_chan_names;

	for (dir = 0; dir < 2; dir++) {
		for (ch_num = 0;
		     ch_num < UX500_MUSB_DMA_NUM_RX_TX_CHANNELS;
		     ch_num++) {
			ux500_channel = &channel_array[ch_num];
			ux500_channel->controller = controller;
			ux500_channel->ch_num = ch_num;
			ux500_channel->is_tx = is_tx;

			dma_channel = &(ux500_channel->channel);
			dma_channel->private_data = ux500_channel;
			dma_channel->status = MUSB_DMA_STATUS_FREE;
			dma_channel->max_len = SZ_16M;

			ux500_channel->dma_chan =
				dma_request_slave_channel(dev, chan_names[ch_num]);

			if (!ux500_channel->dma_chan)
				ux500_channel->dma_chan =
					dma_request_channel(mask,
							    data ?
							    data->dma_filter :
							    NULL,
							    param_array ?
							    param_array[ch_num] :
							    NULL);

			if (!ux500_channel->dma_chan) {
				ERR("Dma pipe allocation error dir=%d ch=%d\n",
					dir, ch_num);

				/* Release already allocated channels */
				ux500_dma_controller_stop(controller);

				return -EBUSY;
			}

		}

		/* Prepare the loop for TX channels */
		channel_array = controller->tx_channel;
		param_array = data ? data->dma_tx_param_array : NULL;
		chan_names = (char **)oep_chan_names;
		is_tx = 1;
	}

	return 0;
}