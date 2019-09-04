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
struct netvsc_device {int tx_disable; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  virt_wmb () ; 

__attribute__((used)) static void netvsc_tx_enable(struct netvsc_device *nvscdev,
			     struct net_device *ndev)
{
	nvscdev->tx_disable = false;
	virt_wmb(); /* ensure queue wake up mechanism is on */

	netif_tx_wake_all_queues(ndev);
}