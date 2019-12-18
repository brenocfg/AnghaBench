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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NETDEV_UNREGISTER ; 
 int /*<<< orphan*/  __LINK_STATE_LINKWATCH_PENDING ; 
 int /*<<< orphan*/  __rtnl_unlock () ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  linkwatch_forget_dev (struct net_device*) ; 
 int /*<<< orphan*/  linkwatch_run_queue () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int netdev_refcnt_read (struct net_device*) ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void netdev_wait_allrefs(struct net_device *dev)
{
	unsigned long rebroadcast_time, warning_time;
	int refcnt;

	linkwatch_forget_dev(dev);

	rebroadcast_time = warning_time = jiffies;
	refcnt = netdev_refcnt_read(dev);

	while (refcnt != 0) {
		if (time_after(jiffies, rebroadcast_time + 1 * HZ)) {
			rtnl_lock();

			/* Rebroadcast unregister notification */
			call_netdevice_notifiers(NETDEV_UNREGISTER, dev);

			__rtnl_unlock();
			rcu_barrier();
			rtnl_lock();

			if (test_bit(__LINK_STATE_LINKWATCH_PENDING,
				     &dev->state)) {
				/* We must not have linkwatch events
				 * pending on unregister. If this
				 * happens, we simply run the queue
				 * unscheduled, resulting in a noop
				 * for this device.
				 */
				linkwatch_run_queue();
			}

			__rtnl_unlock();

			rebroadcast_time = jiffies;
		}

		msleep(250);

		refcnt = netdev_refcnt_read(dev);

		if (refcnt && time_after(jiffies, warning_time + 10 * HZ)) {
			pr_emerg("unregister_netdevice: waiting for %s to become free. Usage count = %d\n",
				 dev->name, refcnt);
			warning_time = jiffies;
		}
	}
}