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
struct tsi108_prv_data {int txhead; int txtail; scalar_t__ link_up; TYPE_1__* txring; int /*<<< orphan*/  txfree; struct sk_buff** txskbs; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int misc; } ;

/* Variables and functions */
 int TSI108_TXRING_LEN ; 
 int TSI108_TX_EOF ; 
 int TSI108_TX_OK ; 
 int TSI108_TX_OWN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tsi108_complete_tx(struct net_device *dev)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	int tx;
	struct sk_buff *skb;
	int release = 0;

	while (!data->txfree || data->txhead != data->txtail) {
		tx = data->txtail;

		if (data->txring[tx].misc & TSI108_TX_OWN)
			break;

		skb = data->txskbs[tx];

		if (!(data->txring[tx].misc & TSI108_TX_OK))
			printk("%s: bad tx packet, misc %x\n",
			       dev->name, data->txring[tx].misc);

		data->txtail = (data->txtail + 1) % TSI108_TXRING_LEN;
		data->txfree++;

		if (data->txring[tx].misc & TSI108_TX_EOF) {
			dev_kfree_skb_any(skb);
			release++;
		}
	}

	if (release) {
		if (is_valid_ether_addr(dev->dev_addr) && data->link_up)
			netif_wake_queue(dev);
	}
}