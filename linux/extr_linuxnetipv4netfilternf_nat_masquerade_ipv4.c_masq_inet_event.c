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
struct netdev_notifier_info {int dummy; } ;
struct in_ifaddr {struct in_device* ifa_dev; } ;
struct in_device {int /*<<< orphan*/  dev; scalar_t__ dead; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int masq_device_event (struct notifier_block*,unsigned long,struct netdev_notifier_info*) ; 
 int /*<<< orphan*/  netdev_notifier_info_init (struct netdev_notifier_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int masq_inet_event(struct notifier_block *this,
			   unsigned long event,
			   void *ptr)
{
	struct in_device *idev = ((struct in_ifaddr *)ptr)->ifa_dev;
	struct netdev_notifier_info info;

	/* The masq_dev_notifier will catch the case of the device going
	 * down.  So if the inetdev is dead and being destroyed we have
	 * no work to do.  Otherwise this is an individual address removal
	 * and we have to perform the flush.
	 */
	if (idev->dead)
		return NOTIFY_DONE;

	netdev_notifier_info_init(&info, idev->dev);
	return masq_device_event(this, event, &info);
}