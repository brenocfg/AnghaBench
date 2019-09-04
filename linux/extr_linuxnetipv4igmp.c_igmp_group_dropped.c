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
struct ip_mc_list {int /*<<< orphan*/  multiaddr; scalar_t__ loaded; struct in_device* interface; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_mc_filter_del (struct in_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igmp_group_dropped(struct ip_mc_list *im)
{
	struct in_device *in_dev = im->interface;
#ifdef CONFIG_IP_MULTICAST
	struct net *net = dev_net(in_dev->dev);
	int reporter;
#endif

	if (im->loaded) {
		im->loaded = 0;
		ip_mc_filter_del(in_dev, im->multiaddr);
	}

#ifdef CONFIG_IP_MULTICAST
	if (im->multiaddr == IGMP_ALL_HOSTS)
		return;
	if (ipv4_is_local_multicast(im->multiaddr) && !net->ipv4.sysctl_igmp_llm_reports)
		return;

	reporter = im->reporter;
	igmp_stop_timer(im);

	if (!in_dev->dead) {
		if (IGMP_V1_SEEN(in_dev))
			return;
		if (IGMP_V2_SEEN(in_dev)) {
			if (reporter)
				igmp_send_report(in_dev, im, IGMP_HOST_LEAVE_MESSAGE);
			return;
		}
		/* IGMPv3 */
		igmpv3_add_delrec(in_dev, im);

		igmp_ifc_event(in_dev);
	}
#endif
}