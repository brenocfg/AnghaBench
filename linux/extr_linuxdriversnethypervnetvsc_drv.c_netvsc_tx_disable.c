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
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  virt_wmb () ; 

__attribute__((used)) static void netvsc_tx_disable(struct netvsc_device *nvscdev,
			      struct net_device *ndev)
{
	if (nvscdev) {
		nvscdev->tx_disable = true;
		virt_wmb(); /* ensure txq will not wake up after stop */
	}

	netif_tx_disable(ndev);
}