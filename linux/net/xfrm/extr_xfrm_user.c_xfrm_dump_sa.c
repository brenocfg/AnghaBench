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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_state_walk {int dummy; } ;
struct xfrm_dump_info {int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; struct sk_buff* out_skb; int /*<<< orphan*/  in_skb; } ;
struct xfrm_address_filter {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int* args; int /*<<< orphan*/  extack; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 size_t XFRMA_ADDRESS_FILTER ; 
 int /*<<< orphan*/  XFRMA_MAX ; 
 size_t XFRMA_PROTO ; 
 int /*<<< orphan*/  dump_one_state ; 
 struct xfrm_address_filter* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nlmsg_parse_deprecated (TYPE_1__*,int /*<<< orphan*/ ,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_walk (struct net*,struct xfrm_state_walk*,int /*<<< orphan*/ ,struct xfrm_dump_info*) ; 
 int /*<<< orphan*/  xfrm_state_walk_init (struct xfrm_state_walk*,int /*<<< orphan*/ ,struct xfrm_address_filter*) ; 
 int /*<<< orphan*/  xfrma_policy ; 

__attribute__((used)) static int xfrm_dump_sa(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_state_walk *walk = (struct xfrm_state_walk *) &cb->args[1];
	struct xfrm_dump_info info;

	BUILD_BUG_ON(sizeof(struct xfrm_state_walk) >
		     sizeof(cb->args) - sizeof(cb->args[0]));

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nlmsg_seq = cb->nlh->nlmsg_seq;
	info.nlmsg_flags = NLM_F_MULTI;

	if (!cb->args[0]) {
		struct nlattr *attrs[XFRMA_MAX+1];
		struct xfrm_address_filter *filter = NULL;
		u8 proto = 0;
		int err;

		err = nlmsg_parse_deprecated(cb->nlh, 0, attrs, XFRMA_MAX,
					     xfrma_policy, cb->extack);
		if (err < 0)
			return err;

		if (attrs[XFRMA_ADDRESS_FILTER]) {
			filter = kmemdup(nla_data(attrs[XFRMA_ADDRESS_FILTER]),
					 sizeof(*filter), GFP_KERNEL);
			if (filter == NULL)
				return -ENOMEM;
		}

		if (attrs[XFRMA_PROTO])
			proto = nla_get_u8(attrs[XFRMA_PROTO]);

		xfrm_state_walk_init(walk, proto, filter);
		cb->args[0] = 1;
	}

	(void) xfrm_state_walk(net, walk, dump_one_state, &info);

	return skb->len;
}