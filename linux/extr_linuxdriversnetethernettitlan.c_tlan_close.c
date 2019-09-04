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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  tlan_free_lists (struct net_device*) ; 
 int /*<<< orphan*/  tlan_stop (struct net_device*) ; 

__attribute__((used)) static int tlan_close(struct net_device *dev)
{
	tlan_stop(dev);

	free_irq(dev->irq, dev);
	tlan_free_lists(dev);
	TLAN_DBG(TLAN_DEBUG_GNRL, "Device %s closed.\n", dev->name);

	return 0;

}