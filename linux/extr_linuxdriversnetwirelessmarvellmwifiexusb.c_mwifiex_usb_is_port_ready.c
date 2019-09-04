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
struct usb_card_rec {TYPE_2__* port; } ;
struct mwifiex_private {scalar_t__ usb_port; TYPE_1__* adapter; } ;
struct TYPE_4__ {scalar_t__ tx_data_ep; int /*<<< orphan*/  block_status; } ;
struct TYPE_3__ {struct usb_card_rec* card; } ;

/* Variables and functions */
 int MWIFIEX_TX_DATA_PORT ; 

__attribute__((used)) static bool mwifiex_usb_is_port_ready(struct mwifiex_private *priv)
{
	struct usb_card_rec *card = priv->adapter->card;
	int idx;

	for (idx = 0; idx < MWIFIEX_TX_DATA_PORT; idx++) {
		if (priv->usb_port == card->port[idx].tx_data_ep)
			return !card->port[idx].block_status;
	}

	return false;
}