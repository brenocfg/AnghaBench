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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
struct TYPE_2__ {int (* obj_to_nlattr ) (struct sk_buff*,unsigned int const*) ;} ;
struct nf_conntrack_l4proto {TYPE_1__ ctnl_timeout; int /*<<< orphan*/  l4proto; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  CTA_TIMEOUT_DATA ; 
 int /*<<< orphan*/  CTA_TIMEOUT_L3PROTO ; 
 int /*<<< orphan*/  CTA_TIMEOUT_L4PROTO ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNL_SUBSYS_CTNETLINK_TIMEOUT ; 
 unsigned int NLM_F_MULTI ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int nfnl_msg_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,scalar_t__,int,int,unsigned int) ; 
 int stub1 (struct sk_buff*,unsigned int const*) ; 

__attribute__((used)) static int
cttimeout_default_fill_info(struct net *net, struct sk_buff *skb, u32 portid,
			    u32 seq, u32 type, int event, u16 l3num,
			    const struct nf_conntrack_l4proto *l4proto,
			    const unsigned int *timeouts)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;
	unsigned int flags = portid ? NLM_F_MULTI : 0;
	struct nlattr *nest_parms;
	int ret;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK_TIMEOUT, event);
	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*nfmsg), flags);
	if (nlh == NULL)
		goto nlmsg_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family = AF_UNSPEC;
	nfmsg->version = NFNETLINK_V0;
	nfmsg->res_id = 0;

	if (nla_put_be16(skb, CTA_TIMEOUT_L3PROTO, htons(l3num)) ||
	    nla_put_u8(skb, CTA_TIMEOUT_L4PROTO, l4proto->l4proto))
		goto nla_put_failure;

	nest_parms = nla_nest_start(skb, CTA_TIMEOUT_DATA);
	if (!nest_parms)
		goto nla_put_failure;

	ret = l4proto->ctnl_timeout.obj_to_nlattr(skb, timeouts);
	if (ret < 0)
		goto nla_put_failure;

	nla_nest_end(skb, nest_parms);

	nlmsg_end(skb, nlh);
	return skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -1;
}