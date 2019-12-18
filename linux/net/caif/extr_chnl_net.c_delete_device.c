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
struct chnl_net {scalar_t__ netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  unregister_netdevice (scalar_t__) ; 

__attribute__((used)) static int delete_device(struct chnl_net *dev)
{
	ASSERT_RTNL();
	if (dev->netdev)
		unregister_netdevice(dev->netdev);
	return 0;
}