#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  proc_net_devsnmp6; } ;
struct net {TYPE_1__ mib; } ;
struct TYPE_4__ {int /*<<< orphan*/ * proc_dir_entry; } ;
struct inet6_dev {TYPE_2__ stats; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_remove (int /*<<< orphan*/ *) ; 

int snmp6_unregister_dev(struct inet6_dev *idev)
{
	struct net *net = dev_net(idev->dev);
	if (!net->mib.proc_net_devsnmp6)
		return -ENOENT;
	if (!idev->stats.proc_dir_entry)
		return -EINVAL;
	proc_remove(idev->stats.proc_dir_entry);
	idev->stats.proc_dir_entry = NULL;
	return 0;
}