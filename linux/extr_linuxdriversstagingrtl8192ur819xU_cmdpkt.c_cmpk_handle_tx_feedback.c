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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  txfeedback; } ;
struct r8192_priv {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
struct cmd_pkt_tx_feedback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmpk_count_txstatistic (struct net_device*,struct cmd_pkt_tx_feedback*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cmpk_handle_tx_feedback(struct net_device *dev, u8 *pmsg)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct cmd_pkt_tx_feedback rx_tx_fb;

	priv->stats.txfeedback++;

	/* 1. Extract TX feedback info from RFD to temp structure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	 * windows OS. So we have to read the content byte by byte or transfer
	 * endian type before copy the message copy.
	 */
	/* Use pointer to transfer structure memory. */
	memcpy((u8 *)&rx_tx_fb, pmsg, sizeof(struct cmd_pkt_tx_feedback));
	/* 2. Use tx feedback info to count TX statistics. */
	cmpk_count_txstatistic(dev, &rx_tx_fb);
	/* Comment previous method for TX statistic function. */
	/* Collect info TX feedback packet to fill TCB. */
	/* We can not know the packet length and transmit type: broadcast or uni
	 * or multicast.
	 */
}