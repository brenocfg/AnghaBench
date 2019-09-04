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
struct eth_dev {int /*<<< orphan*/  net; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

void gether_cleanup(struct eth_dev *dev)
{
	if (!dev)
		return;

	unregister_netdev(dev->net);
	flush_work(&dev->work);
	free_netdev(dev->net);
}