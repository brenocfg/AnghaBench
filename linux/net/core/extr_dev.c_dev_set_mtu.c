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
struct netlink_ext_ack {scalar_t__ _msg; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  extack ;

/* Variables and functions */
 int dev_set_mtu_ext (struct net_device*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  memset (struct netlink_ext_ack*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_err_ratelimited (char*,int /*<<< orphan*/ ,scalar_t__) ; 

int dev_set_mtu(struct net_device *dev, int new_mtu)
{
	struct netlink_ext_ack extack;
	int err;

	memset(&extack, 0, sizeof(extack));
	err = dev_set_mtu_ext(dev, new_mtu, &extack);
	if (err && extack._msg)
		net_err_ratelimited("%s: %s\n", dev->name, extack._msg);
	return err;
}