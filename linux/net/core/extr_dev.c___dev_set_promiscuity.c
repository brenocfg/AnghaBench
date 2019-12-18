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
struct net_device {unsigned int flags; scalar_t__ promiscuity; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  AUDIT_ANOM_PROMISCUOUS ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  __dev_notify_flags (struct net_device*,unsigned int,int) ; 
 int /*<<< orphan*/  audit_context () ; 
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_uid_gid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_change_rx_flags (struct net_device*,int) ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dev_set_promiscuity(struct net_device *dev, int inc, bool notify)
{
	unsigned int old_flags = dev->flags;
	kuid_t uid;
	kgid_t gid;

	ASSERT_RTNL();

	dev->flags |= IFF_PROMISC;
	dev->promiscuity += inc;
	if (dev->promiscuity == 0) {
		/*
		 * Avoid overflow.
		 * If inc causes overflow, untouch promisc and return error.
		 */
		if (inc < 0)
			dev->flags &= ~IFF_PROMISC;
		else {
			dev->promiscuity -= inc;
			pr_warn("%s: promiscuity touches roof, set promiscuity failed. promiscuity feature of device might be broken.\n",
				dev->name);
			return -EOVERFLOW;
		}
	}
	if (dev->flags != old_flags) {
		pr_info("device %s %s promiscuous mode\n",
			dev->name,
			dev->flags & IFF_PROMISC ? "entered" : "left");
		if (audit_enabled) {
			current_uid_gid(&uid, &gid);
			audit_log(audit_context(), GFP_ATOMIC,
				  AUDIT_ANOM_PROMISCUOUS,
				  "dev=%s prom=%d old_prom=%d auid=%u uid=%u gid=%u ses=%u",
				  dev->name, (dev->flags & IFF_PROMISC),
				  (old_flags & IFF_PROMISC),
				  from_kuid(&init_user_ns, audit_get_loginuid(current)),
				  from_kuid(&init_user_ns, uid),
				  from_kgid(&init_user_ns, gid),
				  audit_get_sessionid(current));
		}

		dev_change_rx_flags(dev, IFF_PROMISC);
	}
	if (notify)
		__dev_notify_flags(dev, old_flags, IFF_PROMISC);
	return 0;
}