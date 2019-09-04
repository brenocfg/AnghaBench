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
struct vnt_private {int exist_sw_net_addr; scalar_t__ preamble_type; int /*<<< orphan*/  auto_fb_ctrl; int /*<<< orphan*/  bb_type; int /*<<< orphan*/  packet_type; int /*<<< orphan*/  op_mode; int /*<<< orphan*/  long_retry_limit; int /*<<< orphan*/  short_retry_limit; scalar_t__ num_rcb; scalar_t__ num_tx_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_FB_0 ; 
 int /*<<< orphan*/  BBP_TYPE_DEF ; 
 scalar_t__ CB_MAX_RX_DESC ; 
 scalar_t__ CB_MAX_TX_DESC ; 
 scalar_t__ CB_MIN_RX_DESC ; 
 scalar_t__ CB_MIN_TX_DESC ; 
 int /*<<< orphan*/  LONG_RETRY_DEF ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ RX_DESC_DEF0 ; 
 int /*<<< orphan*/  SHORT_RETRY_DEF ; 
 scalar_t__ TX_DESC_DEF0 ; 
 scalar_t__ vnt_rx_buffers ; 
 scalar_t__ vnt_tx_buffers ; 

__attribute__((used)) static void vnt_set_options(struct vnt_private *priv)
{
	/* Set number of TX buffers */
	if (vnt_tx_buffers < CB_MIN_TX_DESC || vnt_tx_buffers > CB_MAX_TX_DESC)
		priv->num_tx_context = TX_DESC_DEF0;
	else
		priv->num_tx_context = vnt_tx_buffers;

	/* Set number of RX buffers */
	if (vnt_rx_buffers < CB_MIN_RX_DESC || vnt_rx_buffers > CB_MAX_RX_DESC)
		priv->num_rcb = RX_DESC_DEF0;
	else
		priv->num_rcb = vnt_rx_buffers;

	priv->short_retry_limit = SHORT_RETRY_DEF;
	priv->long_retry_limit = LONG_RETRY_DEF;
	priv->op_mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->bb_type = BBP_TYPE_DEF;
	priv->packet_type = priv->bb_type;
	priv->auto_fb_ctrl = AUTO_FB_0;
	priv->preamble_type = 0;
	priv->exist_sw_net_addr = false;
}