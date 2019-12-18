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
typedef  int /*<<< orphan*/  u32 ;
struct tcamsg {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
#define  RTM_DELACTION 130 
#define  RTM_GETACTION 129 
#define  RTM_NEWACTION 128 
 size_t TCA_ACT_TAB ; 
 int /*<<< orphan*/  TCA_ROOT_MAX ; 
 int /*<<< orphan*/  netlink_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int tca_action_gd (struct net*,struct nlattr*,struct nlmsghdr*,int /*<<< orphan*/ ,int const,struct netlink_ext_ack*) ; 
 int tcf_action_add (struct net*,struct nlattr*,struct nlmsghdr*,int /*<<< orphan*/ ,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int tc_ctl_action(struct sk_buff *skb, struct nlmsghdr *n,
			 struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tca[TCA_ROOT_MAX + 1];
	u32 portid = skb ? NETLINK_CB(skb).portid : 0;
	int ret = 0, ovr = 0;

	if ((n->nlmsg_type != RTM_GETACTION) &&
	    !netlink_capable(skb, CAP_NET_ADMIN))
		return -EPERM;

	ret = nlmsg_parse_deprecated(n, sizeof(struct tcamsg), tca,
				     TCA_ROOT_MAX, NULL, extack);
	if (ret < 0)
		return ret;

	if (tca[TCA_ACT_TAB] == NULL) {
		NL_SET_ERR_MSG(extack, "Netlink action attributes missing");
		return -EINVAL;
	}

	/* n->nlmsg_flags & NLM_F_CREATE */
	switch (n->nlmsg_type) {
	case RTM_NEWACTION:
		/* we are going to assume all other flags
		 * imply create only if it doesn't exist
		 * Note that CREATE | EXCL implies that
		 * but since we want avoid ambiguity (eg when flags
		 * is zero) then just set this
		 */
		if (n->nlmsg_flags & NLM_F_REPLACE)
			ovr = 1;
		ret = tcf_action_add(net, tca[TCA_ACT_TAB], n, portid, ovr,
				     extack);
		break;
	case RTM_DELACTION:
		ret = tca_action_gd(net, tca[TCA_ACT_TAB], n,
				    portid, RTM_DELACTION, extack);
		break;
	case RTM_GETACTION:
		ret = tca_action_gd(net, tca[TCA_ACT_TAB], n,
				    portid, RTM_GETACTION, extack);
		break;
	default:
		BUG();
	}

	return ret;
}