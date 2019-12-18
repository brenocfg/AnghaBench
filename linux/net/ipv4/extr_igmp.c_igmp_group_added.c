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
struct TYPE_2__ {int /*<<< orphan*/  sysctl_igmp_qrv; int /*<<< orphan*/  sysctl_igmp_llm_reports; } ;
struct net {TYPE_1__ ipv4; } ;
struct ip_mc_list {int loaded; scalar_t__ sfmode; int /*<<< orphan*/  crcount; int /*<<< orphan*/  lock; int /*<<< orphan*/  unsolicit_count; int /*<<< orphan*/  multiaddr; struct in_device* interface; } ;
struct in_device {scalar_t__ mr_qrv; scalar_t__ dead; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGMP_ALL_HOSTS ; 
 int /*<<< orphan*/  IGMP_INITIAL_REPORT_DELAY ; 
 scalar_t__ IGMP_V1_SEEN (struct in_device*) ; 
 scalar_t__ IGMP_V2_SEEN (struct in_device*) ; 
 scalar_t__ MCAST_EXCLUDE ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igmp_ifc_event (struct in_device*) ; 
 int /*<<< orphan*/  igmp_start_timer (struct ip_mc_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_mc_filter_add (struct in_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igmp_group_added(struct ip_mc_list *im)
{
	struct in_device *in_dev = im->interface;
#ifdef CONFIG_IP_MULTICAST
	struct net *net = dev_net(in_dev->dev);
#endif

	if (im->loaded == 0) {
		im->loaded = 1;
		ip_mc_filter_add(in_dev, im->multiaddr);
	}

#ifdef CONFIG_IP_MULTICAST
	if (im->multiaddr == IGMP_ALL_HOSTS)
		return;
	if (ipv4_is_local_multicast(im->multiaddr) && !net->ipv4.sysctl_igmp_llm_reports)
		return;

	if (in_dev->dead)
		return;

	im->unsolicit_count = net->ipv4.sysctl_igmp_qrv;
	if (IGMP_V1_SEEN(in_dev) || IGMP_V2_SEEN(in_dev)) {
		spin_lock_bh(&im->lock);
		igmp_start_timer(im, IGMP_INITIAL_REPORT_DELAY);
		spin_unlock_bh(&im->lock);
		return;
	}
	/* else, v3 */

	/* Based on RFC3376 5.1, for newly added INCLUDE SSM, we should
	 * not send filter-mode change record as the mode should be from
	 * IN() to IN(A).
	 */
	if (im->sfmode == MCAST_EXCLUDE)
		im->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;

	igmp_ifc_event(in_dev);
#endif
}