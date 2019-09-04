#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_csum; } ;
struct TYPE_5__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_3__ perf_stats; TYPE_2__ options; TYPE_1__* dev; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int NETIF_F_RXCSUM ; 
 int QETH_HDR_EXT_CSUM_TRANSP_REQ ; 

__attribute__((used)) static inline void qeth_rx_csum(struct qeth_card *card, struct sk_buff *skb,
				u8 flags)
{
	if ((card->dev->features & NETIF_F_RXCSUM) &&
	    (flags & QETH_HDR_EXT_CSUM_TRANSP_REQ)) {
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		if (card->options.performance_stats)
			card->perf_stats.rx_csum++;
	} else {
		skb->ip_summed = CHECKSUM_NONE;
	}
}