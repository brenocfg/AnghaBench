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
 int /*<<< orphan*/  TLAN_IGNORE ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  tlan_read_and_clear_stats (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_reset_adapter (struct net_device*) ; 
 int /*<<< orphan*/  tlan_reset_lists (struct net_device*) ; 

__attribute__((used)) static void tlan_start(struct net_device *dev)
{
	tlan_reset_lists(dev);
	/* NOTE: It might not be necessary to read the stats before a
	   reset if you don't care what the values are.
	*/
	tlan_read_and_clear_stats(dev, TLAN_IGNORE);
	tlan_reset_adapter(dev);
	netif_wake_queue(dev);
}