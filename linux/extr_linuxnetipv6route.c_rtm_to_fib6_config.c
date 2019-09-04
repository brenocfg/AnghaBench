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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rtmsg {int rtm_dst_len; int rtm_src_len; scalar_t__ rtm_type; int rtm_flags; int /*<<< orphan*/  rtm_protocol; void* rtm_table; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nl_net; struct nlmsghdr* nlh; int /*<<< orphan*/  portid; } ;
struct fib6_config {int fc_dst_len; int fc_src_len; int fc_flags; scalar_t__ fc_type; int fc_mx_len; int fc_mp_len; int /*<<< orphan*/  fc_expires; int /*<<< orphan*/  fc_encap_type; struct nlattr* fc_encap; void* fc_mp; void* fc_table; void* fc_mx; void* fc_metric; void* fc_ifindex; void* fc_prefsrc; int /*<<< orphan*/  fc_src; int /*<<< orphan*/  fc_dst; void* fc_gateway; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long HZ ; 
 unsigned int ICMPV6_ROUTER_PREF_HIGH ; 
 unsigned int ICMPV6_ROUTER_PREF_LOW ; 
 unsigned int ICMPV6_ROUTER_PREF_MEDIUM ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t RTA_DST ; 
 size_t RTA_ENCAP ; 
 size_t RTA_ENCAP_TYPE ; 
 size_t RTA_EXPIRES ; 
 size_t RTA_GATEWAY ; 
 int /*<<< orphan*/  RTA_MAX ; 
 size_t RTA_METRICS ; 
 size_t RTA_MULTIPATH ; 
 size_t RTA_OIF ; 
 size_t RTA_PREF ; 
 size_t RTA_PREFSRC ; 
 size_t RTA_PRIORITY ; 
 size_t RTA_SRC ; 
 size_t RTA_TABLE ; 
 size_t RTA_VIA ; 
 int RTF_CACHE ; 
 int RTF_EXPIRES ; 
 int RTF_GATEWAY ; 
 int RTF_LOCAL ; 
 int RTF_PREF (unsigned int) ; 
 int RTF_REJECT ; 
 int RTF_UP ; 
 int RTM_F_CLONED ; 
 int RTNH_F_ONLINK ; 
 scalar_t__ RTN_BLACKHOLE ; 
 scalar_t__ RTN_LOCAL ; 
 scalar_t__ RTN_PROHIBIT ; 
 scalar_t__ RTN_THROW ; 
 scalar_t__ RTN_UNREACHABLE ; 
 scalar_t__ addrconf_finite_timeout (unsigned long) ; 
 unsigned long addrconf_timeout_fixup (void*,unsigned long) ; 
 int /*<<< orphan*/  jiffies_to_clock_t (unsigned long) ; 
 int lwtunnel_valid_encap_type (int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int lwtunnel_valid_encap_type_attr (void*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  memset (struct fib6_config*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (struct nlattr*) ; 
 void* nla_get_in6_addr (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 unsigned int nla_get_u8 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ *,struct nlattr*,int) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtm_ipv6_policy ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtm_to_fib6_config(struct sk_buff *skb, struct nlmsghdr *nlh,
			      struct fib6_config *cfg,
			      struct netlink_ext_ack *extack)
{
	struct rtmsg *rtm;
	struct nlattr *tb[RTA_MAX+1];
	unsigned int pref;
	int err;

	err = nlmsg_parse(nlh, sizeof(*rtm), tb, RTA_MAX, rtm_ipv6_policy,
			  NULL);
	if (err < 0)
		goto errout;

	err = -EINVAL;
	rtm = nlmsg_data(nlh);
	memset(cfg, 0, sizeof(*cfg));

	cfg->fc_table = rtm->rtm_table;
	cfg->fc_dst_len = rtm->rtm_dst_len;
	cfg->fc_src_len = rtm->rtm_src_len;
	cfg->fc_flags = RTF_UP;
	cfg->fc_protocol = rtm->rtm_protocol;
	cfg->fc_type = rtm->rtm_type;

	if (rtm->rtm_type == RTN_UNREACHABLE ||
	    rtm->rtm_type == RTN_BLACKHOLE ||
	    rtm->rtm_type == RTN_PROHIBIT ||
	    rtm->rtm_type == RTN_THROW)
		cfg->fc_flags |= RTF_REJECT;

	if (rtm->rtm_type == RTN_LOCAL)
		cfg->fc_flags |= RTF_LOCAL;

	if (rtm->rtm_flags & RTM_F_CLONED)
		cfg->fc_flags |= RTF_CACHE;

	cfg->fc_flags |= (rtm->rtm_flags & RTNH_F_ONLINK);

	cfg->fc_nlinfo.portid = NETLINK_CB(skb).portid;
	cfg->fc_nlinfo.nlh = nlh;
	cfg->fc_nlinfo.nl_net = sock_net(skb->sk);

	if (tb[RTA_GATEWAY]) {
		cfg->fc_gateway = nla_get_in6_addr(tb[RTA_GATEWAY]);
		cfg->fc_flags |= RTF_GATEWAY;
	}
	if (tb[RTA_VIA]) {
		NL_SET_ERR_MSG(extack, "IPv6 does not support RTA_VIA attribute");
		goto errout;
	}

	if (tb[RTA_DST]) {
		int plen = (rtm->rtm_dst_len + 7) >> 3;

		if (nla_len(tb[RTA_DST]) < plen)
			goto errout;

		nla_memcpy(&cfg->fc_dst, tb[RTA_DST], plen);
	}

	if (tb[RTA_SRC]) {
		int plen = (rtm->rtm_src_len + 7) >> 3;

		if (nla_len(tb[RTA_SRC]) < plen)
			goto errout;

		nla_memcpy(&cfg->fc_src, tb[RTA_SRC], plen);
	}

	if (tb[RTA_PREFSRC])
		cfg->fc_prefsrc = nla_get_in6_addr(tb[RTA_PREFSRC]);

	if (tb[RTA_OIF])
		cfg->fc_ifindex = nla_get_u32(tb[RTA_OIF]);

	if (tb[RTA_PRIORITY])
		cfg->fc_metric = nla_get_u32(tb[RTA_PRIORITY]);

	if (tb[RTA_METRICS]) {
		cfg->fc_mx = nla_data(tb[RTA_METRICS]);
		cfg->fc_mx_len = nla_len(tb[RTA_METRICS]);
	}

	if (tb[RTA_TABLE])
		cfg->fc_table = nla_get_u32(tb[RTA_TABLE]);

	if (tb[RTA_MULTIPATH]) {
		cfg->fc_mp = nla_data(tb[RTA_MULTIPATH]);
		cfg->fc_mp_len = nla_len(tb[RTA_MULTIPATH]);

		err = lwtunnel_valid_encap_type_attr(cfg->fc_mp,
						     cfg->fc_mp_len, extack);
		if (err < 0)
			goto errout;
	}

	if (tb[RTA_PREF]) {
		pref = nla_get_u8(tb[RTA_PREF]);
		if (pref != ICMPV6_ROUTER_PREF_LOW &&
		    pref != ICMPV6_ROUTER_PREF_HIGH)
			pref = ICMPV6_ROUTER_PREF_MEDIUM;
		cfg->fc_flags |= RTF_PREF(pref);
	}

	if (tb[RTA_ENCAP])
		cfg->fc_encap = tb[RTA_ENCAP];

	if (tb[RTA_ENCAP_TYPE]) {
		cfg->fc_encap_type = nla_get_u16(tb[RTA_ENCAP_TYPE]);

		err = lwtunnel_valid_encap_type(cfg->fc_encap_type, extack);
		if (err < 0)
			goto errout;
	}

	if (tb[RTA_EXPIRES]) {
		unsigned long timeout = addrconf_timeout_fixup(nla_get_u32(tb[RTA_EXPIRES]), HZ);

		if (addrconf_finite_timeout(timeout)) {
			cfg->fc_expires = jiffies_to_clock_t(timeout * HZ);
			cfg->fc_flags |= RTF_EXPIRES;
		}
	}

	err = 0;
errout:
	return err;
}