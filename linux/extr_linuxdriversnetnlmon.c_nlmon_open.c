#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  module; struct net_device* dev; } ;
struct nlmon {TYPE_1__ nt; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 struct nlmon* netdev_priv (struct net_device*) ; 
 int netlink_add_tap (TYPE_1__*) ; 

__attribute__((used)) static int nlmon_open(struct net_device *dev)
{
	struct nlmon *nlmon = netdev_priv(dev);

	nlmon->nt.dev = dev;
	nlmon->nt.module = THIS_MODULE;
	return netlink_add_tap(&nlmon->nt);
}