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
struct net_device {scalar_t__ dev_addr; } ;
typedef  int /*<<< orphan*/  rose_address ;

/* Variables and functions */
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int rose_add_loopback_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rose_open(struct net_device *dev)
{
	int err;

	err = rose_add_loopback_node((rose_address *)dev->dev_addr);
	if (err)
		return err;

	netif_start_queue(dev);

	return 0;
}