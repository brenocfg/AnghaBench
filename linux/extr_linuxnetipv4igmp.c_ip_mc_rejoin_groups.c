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
struct in_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ip_mc_rejoin_groups(struct in_device *in_dev)
{
#ifdef CONFIG_IP_MULTICAST
	struct ip_mc_list *im;
	int type;
	struct net *net = dev_net(in_dev->dev);

	ASSERT_RTNL();

	for_each_pmc_rtnl(in_dev, im) {
		if (im->multiaddr == IGMP_ALL_HOSTS)
			continue;
		if (ipv4_is_local_multicast(im->multiaddr) &&
		    !net->ipv4.sysctl_igmp_llm_reports)
			continue;

		/* a failover is happening and switches
		 * must be notified immediately
		 */
		if (IGMP_V1_SEEN(in_dev))
			type = IGMP_HOST_MEMBERSHIP_REPORT;
		else if (IGMP_V2_SEEN(in_dev))
			type = IGMPV2_HOST_MEMBERSHIP_REPORT;
		else
			type = IGMPV3_HOST_MEMBERSHIP_REPORT;
		igmp_send_report(in_dev, im, type);
	}
#endif
}