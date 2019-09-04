#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct channel_data {TYPE_3__* rx_skb; TYPE_2__* cosa; TYPE_6__* netdev; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;
struct TYPE_9__ {TYPE_6__* dev; int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {scalar_t__ rxsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdlc_type_trans (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  netif_rx (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (TYPE_3__*) ; 

__attribute__((used)) static int cosa_net_rx_done(struct channel_data *chan)
{
	if (!chan->rx_skb) {
		pr_warn("%s: rx_done with empty skb!\n", chan->name);
		chan->netdev->stats.rx_errors++;
		chan->netdev->stats.rx_frame_errors++;
		return 0;
	}
	chan->rx_skb->protocol = hdlc_type_trans(chan->rx_skb, chan->netdev);
	chan->rx_skb->dev = chan->netdev;
	skb_reset_mac_header(chan->rx_skb);
	chan->netdev->stats.rx_packets++;
	chan->netdev->stats.rx_bytes += chan->cosa->rxsize;
	netif_rx(chan->rx_skb);
	chan->rx_skb = NULL;
	return 0;
}