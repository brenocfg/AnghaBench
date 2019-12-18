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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int len; } ;
struct nlmsghdr {int dummy; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
struct nf_acct {scalar_t__ flags; scalar_t__ data; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  NFACCT_BYTES ; 
 int /*<<< orphan*/  NFACCT_FLAGS ; 
 int NFACCT_F_QUOTA ; 
 int /*<<< orphan*/  NFACCT_NAME ; 
 int /*<<< orphan*/  NFACCT_OVERQUOTA_BIT ; 
 int /*<<< orphan*/  NFACCT_PAD ; 
 int /*<<< orphan*/  NFACCT_PKTS ; 
 int /*<<< orphan*/  NFACCT_QUOTA ; 
 int /*<<< orphan*/  NFACCT_USE ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 scalar_t__ NFNL_MSG_ACCT_GET_CTRZERO ; 
 int /*<<< orphan*/  NFNL_SUBSYS_ACCT ; 
 unsigned int NLM_F_MULTI ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int nfnl_msg_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,scalar_t__,int,int,unsigned int) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static int
nfnl_acct_fill_info(struct sk_buff *skb, u32 portid, u32 seq, u32 type,
		   int event, struct nf_acct *acct)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;
	unsigned int flags = portid ? NLM_F_MULTI : 0;
	u64 pkts, bytes;
	u32 old_flags;

	event = nfnl_msg_type(NFNL_SUBSYS_ACCT, event);
	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*nfmsg), flags);
	if (nlh == NULL)
		goto nlmsg_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family = AF_UNSPEC;
	nfmsg->version = NFNETLINK_V0;
	nfmsg->res_id = 0;

	if (nla_put_string(skb, NFACCT_NAME, acct->name))
		goto nla_put_failure;

	old_flags = acct->flags;
	if (type == NFNL_MSG_ACCT_GET_CTRZERO) {
		pkts = atomic64_xchg(&acct->pkts, 0);
		bytes = atomic64_xchg(&acct->bytes, 0);
		smp_mb__before_atomic();
		if (acct->flags & NFACCT_F_QUOTA)
			clear_bit(NFACCT_OVERQUOTA_BIT, &acct->flags);
	} else {
		pkts = atomic64_read(&acct->pkts);
		bytes = atomic64_read(&acct->bytes);
	}
	if (nla_put_be64(skb, NFACCT_PKTS, cpu_to_be64(pkts),
			 NFACCT_PAD) ||
	    nla_put_be64(skb, NFACCT_BYTES, cpu_to_be64(bytes),
			 NFACCT_PAD) ||
	    nla_put_be32(skb, NFACCT_USE, htonl(refcount_read(&acct->refcnt))))
		goto nla_put_failure;
	if (acct->flags & NFACCT_F_QUOTA) {
		u64 *quota = (u64 *)acct->data;

		if (nla_put_be32(skb, NFACCT_FLAGS, htonl(old_flags)) ||
		    nla_put_be64(skb, NFACCT_QUOTA, cpu_to_be64(*quota),
				 NFACCT_PAD))
			goto nla_put_failure;
	}
	nlmsg_end(skb, nlh);
	return skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -1;
}