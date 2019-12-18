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
struct notifier_block {int dummy; } ;
struct net {int dummy; } ;
struct in_ifaddr {struct in_device* ifa_dev; } ;
struct in_device {scalar_t__ dead; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_cmp ; 
 int /*<<< orphan*/  nf_ct_iterate_cleanup_net (struct net*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int masq_inet_event(struct notifier_block *this,
			   unsigned long event,
			   void *ptr)
{
	struct in_device *idev = ((struct in_ifaddr *)ptr)->ifa_dev;
	struct net *net = dev_net(idev->dev);

	/* The masq_dev_notifier will catch the case of the device going
	 * down.  So if the inetdev is dead and being destroyed we have
	 * no work to do.  Otherwise this is an individual address removal
	 * and we have to perform the flush.
	 */
	if (idev->dead)
		return NOTIFY_DONE;

	if (event == NETDEV_DOWN)
		nf_ct_iterate_cleanup_net(net, inet_cmp, ptr, 0, 0);

	return NOTIFY_DONE;
}