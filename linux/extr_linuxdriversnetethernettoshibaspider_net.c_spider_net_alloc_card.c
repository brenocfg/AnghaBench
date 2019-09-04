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
struct spider_net_descr {int dummy; } ;
struct TYPE_4__ {int num_desc; scalar_t__ ring; } ;
struct TYPE_3__ {int num_desc; scalar_t__ ring; } ;
struct spider_net_card {scalar_t__ darray; TYPE_2__ tx_chain; TYPE_1__ rx_chain; int /*<<< orphan*/  tx_timeout_task_counter; int /*<<< orphan*/  waitq; int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  msg_enable; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIDER_NET_DEFAULT_MSG ; 
 struct net_device* alloc_etherdev (size_t) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 int rx_descriptors ; 
 int /*<<< orphan*/  spider_net_tx_timeout_task ; 
 int tx_descriptors ; 

__attribute__((used)) static struct spider_net_card *
spider_net_alloc_card(void)
{
	struct net_device *netdev;
	struct spider_net_card *card;
	size_t alloc_size;

	alloc_size = sizeof(struct spider_net_card) +
	   (tx_descriptors + rx_descriptors) * sizeof(struct spider_net_descr);
	netdev = alloc_etherdev(alloc_size);
	if (!netdev)
		return NULL;

	card = netdev_priv(netdev);
	card->netdev = netdev;
	card->msg_enable = SPIDER_NET_DEFAULT_MSG;
	INIT_WORK(&card->tx_timeout_task, spider_net_tx_timeout_task);
	init_waitqueue_head(&card->waitq);
	atomic_set(&card->tx_timeout_task_counter, 0);

	card->rx_chain.num_desc = rx_descriptors;
	card->rx_chain.ring = card->darray;
	card->tx_chain.num_desc = tx_descriptors;
	card->tx_chain.ring = card->darray + rx_descriptors;

	return card;
}