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
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct masq_dev_work {int /*<<< orphan*/  work; struct net* net; int /*<<< orphan*/  ifindex; } ;
struct inet6_ifaddr {TYPE_1__* idev; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_WORK_COUNT ; 
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (struct net_device const*) ; 
 int /*<<< orphan*/  iterate_cleanup_work ; 
 struct masq_dev_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct net* maybe_get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v6_worker_count ; 

__attribute__((used)) static int masq_inet6_event(struct notifier_block *this,
			    unsigned long event, void *ptr)
{
	struct inet6_ifaddr *ifa = ptr;
	const struct net_device *dev;
	struct masq_dev_work *w;
	struct net *net;

	if (event != NETDEV_DOWN ||
	    atomic_read(&v6_worker_count) >= MAX_WORK_COUNT)
		return NOTIFY_DONE;

	dev = ifa->idev->dev;
	net = maybe_get_net(dev_net(dev));
	if (!net)
		return NOTIFY_DONE;

	if (!try_module_get(THIS_MODULE))
		goto err_module;

	w = kmalloc(sizeof(*w), GFP_ATOMIC);
	if (w) {
		atomic_inc(&v6_worker_count);

		INIT_WORK(&w->work, iterate_cleanup_work);
		w->ifindex = dev->ifindex;
		w->net = net;
		schedule_work(&w->work);

		return NOTIFY_DONE;
	}

	module_put(THIS_MODULE);
 err_module:
	put_net(net);
	return NOTIFY_DONE;
}