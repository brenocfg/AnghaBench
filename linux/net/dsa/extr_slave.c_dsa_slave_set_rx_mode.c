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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_mc_sync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_sync (struct net_device*,struct net_device*) ; 
 struct net_device* dsa_slave_to_master (struct net_device*) ; 

__attribute__((used)) static void dsa_slave_set_rx_mode(struct net_device *dev)
{
	struct net_device *master = dsa_slave_to_master(dev);

	dev_mc_sync(master, dev);
	dev_uc_sync(master, dev);
}