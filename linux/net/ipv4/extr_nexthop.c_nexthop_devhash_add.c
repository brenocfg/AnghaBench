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
struct TYPE_3__ {struct net_device* nhc_dev; } ;
struct nh_info {int /*<<< orphan*/  dev_hash; TYPE_1__ fib_nhc; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_4__ {struct hlist_head* devhash; } ;
struct net {TYPE_2__ nexthop; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 unsigned int nh_dev_hashfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nexthop_devhash_add(struct net *net, struct nh_info *nhi)
{
	struct net_device *dev = nhi->fib_nhc.nhc_dev;
	struct hlist_head *head;
	unsigned int hash;

	WARN_ON(!dev);

	hash = nh_dev_hashfn(dev->ifindex);
	head = &net->nexthop.devhash[hash];
	hlist_add_head(&nhi->dev_hash, head);
}