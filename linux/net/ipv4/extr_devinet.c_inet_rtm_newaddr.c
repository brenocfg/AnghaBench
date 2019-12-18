#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mc_autojoin_sk; } ;
struct net {TYPE_1__ ipv4; } ;
struct in_ifaddr {int ifa_flags; scalar_t__ ifa_rt_priority; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EEXIST ; 
 int IFA_F_MCAUTOJOIN ; 
 int /*<<< orphan*/  INFINITY_LIFE_TIME ; 
 scalar_t__ IS_ERR (struct in_ifaddr*) ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int PTR_ERR (struct in_ifaddr*) ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int __inet_insert_ifa (struct in_ifaddr*,struct nlmsghdr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_lifetime_work ; 
 int /*<<< orphan*/  fib_modify_prefix_metric (struct in_ifaddr*,scalar_t__) ; 
 struct in_ifaddr* find_matching_ifa (struct in_ifaddr*) ; 
 int /*<<< orphan*/  inet_free_ifa (struct in_ifaddr*) ; 
 int ip_mc_config (int /*<<< orphan*/ ,int,struct in_ifaddr*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct in_ifaddr* rtm_to_ifaddr (struct net*,struct nlmsghdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtmsg_ifa (int /*<<< orphan*/ ,struct in_ifaddr*,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ifa_lifetime (struct in_ifaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int inet_rtm_newaddr(struct sk_buff *skb, struct nlmsghdr *nlh,
			    struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct in_ifaddr *ifa;
	struct in_ifaddr *ifa_existing;
	__u32 valid_lft = INFINITY_LIFE_TIME;
	__u32 prefered_lft = INFINITY_LIFE_TIME;

	ASSERT_RTNL();

	ifa = rtm_to_ifaddr(net, nlh, &valid_lft, &prefered_lft, extack);
	if (IS_ERR(ifa))
		return PTR_ERR(ifa);

	ifa_existing = find_matching_ifa(ifa);
	if (!ifa_existing) {
		/* It would be best to check for !NLM_F_CREATE here but
		 * userspace already relies on not having to provide this.
		 */
		set_ifa_lifetime(ifa, valid_lft, prefered_lft);
		if (ifa->ifa_flags & IFA_F_MCAUTOJOIN) {
			int ret = ip_mc_config(net->ipv4.mc_autojoin_sk,
					       true, ifa);

			if (ret < 0) {
				inet_free_ifa(ifa);
				return ret;
			}
		}
		return __inet_insert_ifa(ifa, nlh, NETLINK_CB(skb).portid,
					 extack);
	} else {
		u32 new_metric = ifa->ifa_rt_priority;

		inet_free_ifa(ifa);

		if (nlh->nlmsg_flags & NLM_F_EXCL ||
		    !(nlh->nlmsg_flags & NLM_F_REPLACE))
			return -EEXIST;
		ifa = ifa_existing;

		if (ifa->ifa_rt_priority != new_metric) {
			fib_modify_prefix_metric(ifa, new_metric);
			ifa->ifa_rt_priority = new_metric;
		}

		set_ifa_lifetime(ifa, valid_lft, prefered_lft);
		cancel_delayed_work(&check_lifetime_work);
		queue_delayed_work(system_power_efficient_wq,
				&check_lifetime_work, 0);
		rtmsg_ifa(RTM_NEWADDR, ifa, nlh, NETLINK_CB(skb).portid);
	}
	return 0;
}