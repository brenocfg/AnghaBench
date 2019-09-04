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
struct tipc_bearer {int /*<<< orphan*/  pt; int /*<<< orphan*/  media_ptr; } ;
struct net_device {int /*<<< orphan*/  tipc_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_remove_pack (int /*<<< orphan*/ *) ; 
 scalar_t__ rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void tipc_disable_l2_media(struct tipc_bearer *b)
{
	struct net_device *dev;

	dev = (struct net_device *)rtnl_dereference(b->media_ptr);
	dev_remove_pack(&b->pt);
	RCU_INIT_POINTER(dev->tipc_ptr, NULL);
	synchronize_net();
	dev_put(dev);
}