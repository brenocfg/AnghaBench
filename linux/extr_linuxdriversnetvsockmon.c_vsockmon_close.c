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
struct vsockmon {int /*<<< orphan*/  vt; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vsockmon* netdev_priv (struct net_device*) ; 
 int vsock_remove_tap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vsockmon_close(struct net_device *dev)
{
	struct vsockmon *vsockmon = netdev_priv(dev);

	return vsock_remove_tap(&vsockmon->vt);
}