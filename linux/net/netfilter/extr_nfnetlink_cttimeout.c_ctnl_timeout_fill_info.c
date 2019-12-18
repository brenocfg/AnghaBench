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
struct sk_buff {int len; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
struct TYPE_3__ {int (* obj_to_nlattr ) (struct sk_buff*,int /*<<< orphan*/ *) ;} ;
struct nf_conntrack_l4proto {TYPE_1__ ctnl_timeout; int /*<<< orphan*/  l4proto; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  l3num; struct nf_conntrack_l4proto* l4proto; } ;
struct ctnl_timeout {TYPE_2__ timeout; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  CTA_TIMEOUT_DATA ; 
 int /*<<< orphan*/  CTA_TIMEOUT_L3PROTO ; 
 int /*<<< orphan*/  CTA_TIMEOUT_L4PROTO ; 
 int /*<<< orphan*/  CTA_TIMEOUT_NAME ; 
 int /*<<< orphan*/  CTA_TIMEOUT_USE ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNL_SUBSYS_CTNETLINK_TIMEOUT ; 
 unsigned int NLM_F_MULTI ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int nfnl_msg_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,scalar_t__,int,int,unsigned int) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctnl_timeout_fill_info(struct sk_buff *skb, u32 portid, u32 seq, u32 type,
		       int event, struct ctnl_timeout *timeout)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;
	unsigned int flags = portid ? NLM_F_MULTI : 0;
	const struct nf_conntrack_l4proto *l4proto = timeout->timeout.l4proto;
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

	if (nla_put_string(skb, CTA_TIMEOUT_NAME, timeout->name) ||
	    nla_put_be16(skb, CTA_TIMEOUT_L3PROTO,
			 htons(timeout->timeout.l3num)) ||
	    nla_put_u8(skb, CTA_TIMEOUT_L4PROTO, l4proto->l4proto) ||
	    nla_put_be32(skb, CTA_TIMEOUT_USE,
			 htonl(refcount_read(&timeout->refcnt))))
		goto nla_put_failure;

	nest_parms = nla_nest_start(skb, CTA_TIMEOUT_DATA);
	if (!nest_parms)
		goto nla_put_failure;

	ret = l4proto->ctnl_timeout.obj_to_nlattr(skb, &timeout->timeout.data);
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