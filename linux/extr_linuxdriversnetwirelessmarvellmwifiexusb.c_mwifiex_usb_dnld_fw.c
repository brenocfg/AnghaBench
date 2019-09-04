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
struct usb_card_rec {scalar_t__ usb_boot_state; } ;
struct mwifiex_fw_image {int dummy; } ;
struct mwifiex_adapter {scalar_t__ card; } ;

/* Variables and functions */
 scalar_t__ USB8XXX_FW_DNLD ; 
 int mwifiex_prog_fw_w_helper (struct mwifiex_adapter*,struct mwifiex_fw_image*) ; 
 int mwifiex_usb_rx_init (struct mwifiex_adapter*) ; 
 int mwifiex_usb_tx_init (struct mwifiex_adapter*) ; 

__attribute__((used)) static int mwifiex_usb_dnld_fw(struct mwifiex_adapter *adapter,
			struct mwifiex_fw_image *fw)
{
	int ret;
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;

	if (card->usb_boot_state == USB8XXX_FW_DNLD) {
		ret = mwifiex_prog_fw_w_helper(adapter, fw);
		if (ret)
			return -1;

		/* Boot state changes after successful firmware download */
		if (card->usb_boot_state == USB8XXX_FW_DNLD)
			return -1;
	}

	ret = mwifiex_usb_rx_init(adapter);
	if (!ret)
		ret = mwifiex_usb_tx_init(adapter);

	return ret;
}