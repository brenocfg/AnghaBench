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
typedef  scalar_t__ u8 ;
struct usb_card_rec {TYPE_1__* port; } ;
struct mwifiex_private {scalar_t__ bss_role; scalar_t__ usb_port; scalar_t__ media_connected; scalar_t__ bss_started; } ;
struct mwifiex_adapter {int priv_num; struct mwifiex_private** priv; scalar_t__ usb_mc_status; struct usb_card_rec* card; } ;
struct TYPE_2__ {int block_status; scalar_t__ tx_data_ep; } ;

/* Variables and functions */
 scalar_t__ MWIFIEX_BSS_ROLE_STA ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 int MWIFIEX_TX_DATA_PORT ; 
 void* MWIFIEX_USB_EP_DATA ; 

__attribute__((used)) static void mwifiex_usb_port_resync(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = adapter->card;
	u8 active_port = MWIFIEX_USB_EP_DATA;
	struct mwifiex_private *priv = NULL;
	int i;

	if (adapter->usb_mc_status) {
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (!priv)
				continue;
			if ((priv->bss_role == MWIFIEX_BSS_ROLE_UAP &&
			     !priv->bss_started) ||
			    (priv->bss_role == MWIFIEX_BSS_ROLE_STA &&
			     !priv->media_connected))
				priv->usb_port = MWIFIEX_USB_EP_DATA;
		}
		for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++)
			card->port[i].block_status = false;
	} else {
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (!priv)
				continue;
			if ((priv->bss_role == MWIFIEX_BSS_ROLE_UAP &&
			     priv->bss_started) ||
			    (priv->bss_role == MWIFIEX_BSS_ROLE_STA &&
			     priv->media_connected)) {
				active_port = priv->usb_port;
				break;
			}
		}
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (priv)
				priv->usb_port = active_port;
		}
		for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++) {
			if (active_port == card->port[i].tx_data_ep)
				card->port[i].block_status = false;
			else
				card->port[i].block_status = true;
		}
	}
}