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
struct sk_buff {scalar_t__ len; } ;
struct lan78xx_net {int /*<<< orphan*/  done; TYPE_2__* net; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan78xx_rx (struct lan78xx_net*,struct sk_buff*) ; 
 int /*<<< orphan*/  lan78xx_skb_return (struct lan78xx_net*,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static inline void rx_process(struct lan78xx_net *dev, struct sk_buff *skb)
{
	if (!lan78xx_rx(dev, skb)) {
		dev->net->stats.rx_errors++;
		goto done;
	}

	if (skb->len) {
		lan78xx_skb_return(dev, skb);
		return;
	}

	netif_dbg(dev, rx_err, dev->net, "drop\n");
	dev->net->stats.rx_errors++;
done:
	skb_queue_tail(&dev->done, skb);
}