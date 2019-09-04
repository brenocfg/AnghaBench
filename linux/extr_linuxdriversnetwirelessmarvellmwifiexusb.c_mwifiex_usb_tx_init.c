#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int is_hold_timer_set; int /*<<< orphan*/  hold_timer; scalar_t__ hold_tmo_msecs; struct usb_tx_data_port* port; struct mwifiex_adapter* adapter; } ;
struct TYPE_8__ {TYPE_3__ timer_cnxt; int /*<<< orphan*/  aggr_list; } ;
struct usb_tx_data_port {scalar_t__ tx_data_ep; int block_status; TYPE_4__ tx_aggr; TYPE_2__* tx_data_list; scalar_t__ tx_data_ix; } ;
struct TYPE_5__ {void* urb; int /*<<< orphan*/  ep; struct mwifiex_adapter* adapter; } ;
struct usb_card_rec {struct usb_tx_data_port* port; TYPE_1__ tx_cmd; int /*<<< orphan*/  tx_cmd_ep; } ;
struct mwifiex_adapter {scalar_t__ card; } ;
struct TYPE_6__ {scalar_t__ ep; void* urb; struct mwifiex_adapter* adapter; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWIFIEX_TX_DATA_PORT ; 
 int MWIFIEX_TX_DATA_URB ; 
 scalar_t__ MWIFIEX_USB_EP_DATA ; 
 int /*<<< orphan*/  mwifiex_usb_tx_aggr_tmo ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_usb_tx_init(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;
	struct usb_tx_data_port *port;
	int i, j;

	card->tx_cmd.adapter = adapter;
	card->tx_cmd.ep = card->tx_cmd_ep;

	card->tx_cmd.urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!card->tx_cmd.urb)
		return -ENOMEM;

	for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) {
		port = &card->port[i];
		if (!port->tx_data_ep)
			continue;
		port->tx_data_ix = 0;
		skb_queue_head_init(&port->tx_aggr.aggr_list);
		if (port->tx_data_ep == MWIFIEX_USB_EP_DATA)
			port->block_status = false;
		else
			port->block_status = true;
		for (j = 0; j < MWIFIEX_TX_DATA_URB; j++) {
			port->tx_data_list[j].adapter = adapter;
			port->tx_data_list[j].ep = port->tx_data_ep;
			port->tx_data_list[j].urb =
					usb_alloc_urb(0, GFP_KERNEL);
			if (!port->tx_data_list[j].urb)
				return -ENOMEM;
		}

		port->tx_aggr.timer_cnxt.adapter = adapter;
		port->tx_aggr.timer_cnxt.port = port;
		port->tx_aggr.timer_cnxt.is_hold_timer_set = false;
		port->tx_aggr.timer_cnxt.hold_tmo_msecs = 0;
		timer_setup(&port->tx_aggr.timer_cnxt.hold_timer,
			    mwifiex_usb_tx_aggr_tmo, 0);
	}

	return 0;
}