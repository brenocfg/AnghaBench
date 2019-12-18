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
typedef  unsigned long u32 ;
struct tcamsg {scalar_t__ tca__pad2; scalar_t__ tca__pad1; int /*<<< orphan*/  tca_family; } ;
struct tc_action_ops {int (* walk ) (struct net*,struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct tc_action_ops*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  owner; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_len; int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct nla_bitfield32 {unsigned long value; } ;
struct netlink_callback {unsigned long* args; int /*<<< orphan*/  skb; struct nlmsghdr* nlh; int /*<<< orphan*/  extack; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 TYPE_1__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_GETACTION ; 
 int /*<<< orphan*/  TCA_ACT_TAB ; 
 int /*<<< orphan*/  TCA_ROOT_COUNT ; 
 size_t TCA_ROOT_FLAGS ; 
 int /*<<< orphan*/  TCA_ROOT_MAX ; 
 size_t TCA_ROOT_TIME_DELTA ; 
 struct nlattr* find_dump_kind (struct nlattr**) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct nla_bitfield32 nla_get_bitfield32 (struct nlattr*) ; 
 unsigned long nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct tcamsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct net*,struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,struct tc_action_ops*,int /*<<< orphan*/ *) ; 
 struct tc_action_ops* tc_lookup_action (struct nlattr*) ; 
 int /*<<< orphan*/  tcaa_policy ; 

__attribute__((used)) static int tc_dump_action(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct nlmsghdr *nlh;
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;
	struct tc_action_ops *a_o;
	int ret = 0;
	struct tcamsg *t = (struct tcamsg *) nlmsg_data(cb->nlh);
	struct nlattr *tb[TCA_ROOT_MAX + 1];
	struct nlattr *count_attr = NULL;
	unsigned long jiffy_since = 0;
	struct nlattr *kind = NULL;
	struct nla_bitfield32 bf;
	u32 msecs_since = 0;
	u32 act_count = 0;

	ret = nlmsg_parse_deprecated(cb->nlh, sizeof(struct tcamsg), tb,
				     TCA_ROOT_MAX, tcaa_policy, cb->extack);
	if (ret < 0)
		return ret;

	kind = find_dump_kind(tb);
	if (kind == NULL) {
		pr_info("tc_dump_action: action bad kind\n");
		return 0;
	}

	a_o = tc_lookup_action(kind);
	if (a_o == NULL)
		return 0;

	cb->args[2] = 0;
	if (tb[TCA_ROOT_FLAGS]) {
		bf = nla_get_bitfield32(tb[TCA_ROOT_FLAGS]);
		cb->args[2] = bf.value;
	}

	if (tb[TCA_ROOT_TIME_DELTA]) {
		msecs_since = nla_get_u32(tb[TCA_ROOT_TIME_DELTA]);
	}

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			cb->nlh->nlmsg_type, sizeof(*t), 0);
	if (!nlh)
		goto out_module_put;

	if (msecs_since)
		jiffy_since = jiffies - msecs_to_jiffies(msecs_since);

	t = nlmsg_data(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;
	cb->args[3] = jiffy_since;
	count_attr = nla_reserve(skb, TCA_ROOT_COUNT, sizeof(u32));
	if (!count_attr)
		goto out_module_put;

	nest = nla_nest_start_noflag(skb, TCA_ACT_TAB);
	if (nest == NULL)
		goto out_module_put;

	ret = a_o->walk(net, skb, cb, RTM_GETACTION, a_o, NULL);
	if (ret < 0)
		goto out_module_put;

	if (ret > 0) {
		nla_nest_end(skb, nest);
		ret = skb->len;
		act_count = cb->args[1];
		memcpy(nla_data(count_attr), &act_count, sizeof(u32));
		cb->args[1] = 0;
	} else
		nlmsg_trim(skb, b);

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	if (NETLINK_CB(cb->skb).portid && ret)
		nlh->nlmsg_flags |= NLM_F_MULTI;
	module_put(a_o->owner);
	return skb->len;

out_module_put:
	module_put(a_o->owner);
	nlmsg_trim(skb, b);
	return skb->len;
}