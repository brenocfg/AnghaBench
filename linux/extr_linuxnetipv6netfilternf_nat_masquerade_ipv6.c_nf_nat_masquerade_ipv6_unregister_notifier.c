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

/* Variables and functions */
 int /*<<< orphan*/  masq_dev_notifier ; 
 int /*<<< orphan*/  masq_inet6_notifier ; 
 int /*<<< orphan*/  masq_mutex ; 
 scalar_t__ masq_refcnt ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inet6addr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

void nf_nat_masquerade_ipv6_unregister_notifier(void)
{
	mutex_lock(&masq_mutex);
	/* check if the notifier still has clients */
	if (--masq_refcnt > 0)
		goto out_unlock;

	unregister_inet6addr_notifier(&masq_inet6_notifier);
	unregister_netdevice_notifier(&masq_dev_notifier);
out_unlock:
	mutex_unlock(&masq_mutex);
}