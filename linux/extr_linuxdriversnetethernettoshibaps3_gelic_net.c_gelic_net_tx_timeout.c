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
struct net_device {int flags; } ;
struct gelic_card {int /*<<< orphan*/  tx_timeout_task_counter; int /*<<< orphan*/  tx_timeout_task; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct gelic_card* netdev_card (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void gelic_net_tx_timeout(struct net_device *netdev)
{
	struct gelic_card *card;

	card = netdev_card(netdev);
	atomic_inc(&card->tx_timeout_task_counter);
	if (netdev->flags & IFF_UP)
		schedule_work(&card->tx_timeout_task);
	else
		atomic_dec(&card->tx_timeout_task_counter);
}