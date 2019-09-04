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
 int /*<<< orphan*/  netdev_lockdep_set_classes (struct net_device*) ; 

__attribute__((used)) static int lowpan_dev_init(struct net_device *ldev)
{
	netdev_lockdep_set_classes(ldev);

	return 0;
}