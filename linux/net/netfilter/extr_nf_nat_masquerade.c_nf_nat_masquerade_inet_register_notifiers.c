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
 int EOVERFLOW ; 
 int UINT_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  masq_dev_notifier ; 
 int /*<<< orphan*/  masq_inet_notifier ; 
 int /*<<< orphan*/  masq_mutex ; 
 int masq_refcnt ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nf_nat_masquerade_ipv6_register_notifier () ; 
 int register_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

int nf_nat_masquerade_inet_register_notifiers(void)
{
	int ret = 0;

	mutex_lock(&masq_mutex);
	if (WARN_ON_ONCE(masq_refcnt == UINT_MAX)) {
		ret = -EOVERFLOW;
		goto out_unlock;
	}

	/* check if the notifier was already set */
	if (++masq_refcnt > 1)
		goto out_unlock;

	/* Register for device down reports */
	ret = register_netdevice_notifier(&masq_dev_notifier);
	if (ret)
		goto err_dec;
	/* Register IP address change reports */
	ret = register_inetaddr_notifier(&masq_inet_notifier);
	if (ret)
		goto err_unregister;

	ret = nf_nat_masquerade_ipv6_register_notifier();
	if (ret)
		goto err_unreg_inet;

	mutex_unlock(&masq_mutex);
	return ret;
err_unreg_inet:
	unregister_inetaddr_notifier(&masq_inet_notifier);
err_unregister:
	unregister_netdevice_notifier(&masq_dev_notifier);
err_dec:
	masq_refcnt--;
out_unlock:
	mutex_unlock(&masq_mutex);
	return ret;
}