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
struct usb_card_rec {struct urb_context* rx_data_list; } ;
struct urb_context {scalar_t__ skb; } ;
struct mwifiex_adapter {scalar_t__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_RX_DATA_BUF_SIZE ; 
 int MWIFIEX_RX_DATA_URB ; 
 int /*<<< orphan*/  mwifiex_usb_submit_rx_urb (struct urb_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_usb_submit_rem_rx_urbs(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;
	int i;
	struct urb_context *ctx;

	for (i = 0; i < MWIFIEX_RX_DATA_URB; i++) {
		if (card->rx_data_list[i].skb)
			continue;
		ctx = &card->rx_data_list[i];
		mwifiex_usb_submit_rx_urb(ctx, MWIFIEX_RX_DATA_BUF_SIZE);
	}
}