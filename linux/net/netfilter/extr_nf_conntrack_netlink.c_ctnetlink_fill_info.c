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
typedef  scalar_t__ u32 ;
struct sk_buff {int len; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {scalar_t__ res_id; int /*<<< orphan*/  version; int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_TUPLE_ORIG ; 
 int /*<<< orphan*/  CTA_TUPLE_REPLY ; 
 int /*<<< orphan*/  CTA_TUPLE_ZONE ; 
 int /*<<< orphan*/  CTA_ZONE ; 
 int /*<<< orphan*/  IPCTNL_MSG_CT_NEW ; 
 int /*<<< orphan*/  IPS_OFFLOAD_BIT ; 
 int /*<<< orphan*/  IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNL_SUBSYS_CTNETLINK ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_DIR ; 
 int /*<<< orphan*/  NF_CT_ZONE_DIR_ORIG ; 
 int /*<<< orphan*/  NF_CT_ZONE_DIR_REPL ; 
 unsigned int NLM_F_MULTI ; 
 scalar_t__ ctnetlink_dump_acct (struct sk_buff*,struct nf_conn*,scalar_t__) ; 
 scalar_t__ ctnetlink_dump_ct_seq_adj (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_ct_synproxy (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_helpinfo (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_id (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_labels (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_mark (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_master (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_protoinfo (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_secctx (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_status (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_timeout (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_timestamp (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_tuples (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctnetlink_dump_use (struct sk_buff*,struct nf_conn*) ; 
 scalar_t__ ctnetlink_dump_zone_id (struct sk_buff*,int /*<<< orphan*/ ,struct nf_conntrack_zone const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_tuple (struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_zone* nf_ct_zone (struct nf_conn*) ; 
 unsigned int nfnl_msg_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,scalar_t__,scalar_t__,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctnetlink_fill_info(struct sk_buff *skb, u32 portid, u32 seq, u32 type,
		    struct nf_conn *ct)
{
	const struct nf_conntrack_zone *zone;
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;
	struct nlattr *nest_parms;
	unsigned int flags = portid ? NLM_F_MULTI : 0, event;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK, IPCTNL_MSG_CT_NEW);
	nlh = nlmsg_put(skb, portid, seq, event, sizeof(*nfmsg), flags);
	if (nlh == NULL)
		goto nlmsg_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family = nf_ct_l3num(ct);
	nfmsg->version      = NFNETLINK_V0;
	nfmsg->res_id	    = 0;

	zone = nf_ct_zone(ct);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_ORIG);
	if (!nest_parms)
		goto nla_put_failure;
	if (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_DIR_ORIGINAL)) < 0)
		goto nla_put_failure;
	if (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_DIR_ORIG) < 0)
		goto nla_put_failure;
	nla_nest_end(skb, nest_parms);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_REPLY);
	if (!nest_parms)
		goto nla_put_failure;
	if (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_DIR_REPLY)) < 0)
		goto nla_put_failure;
	if (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_DIR_REPL) < 0)
		goto nla_put_failure;
	nla_nest_end(skb, nest_parms);

	if (ctnetlink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAULT_ZONE_DIR) < 0)
		goto nla_put_failure;

	if (ctnetlink_dump_status(skb, ct) < 0 ||
	    ctnetlink_dump_acct(skb, ct, type) < 0 ||
	    ctnetlink_dump_timestamp(skb, ct) < 0 ||
	    ctnetlink_dump_helpinfo(skb, ct) < 0 ||
	    ctnetlink_dump_mark(skb, ct) < 0 ||
	    ctnetlink_dump_secctx(skb, ct) < 0 ||
	    ctnetlink_dump_labels(skb, ct) < 0 ||
	    ctnetlink_dump_id(skb, ct) < 0 ||
	    ctnetlink_dump_use(skb, ct) < 0 ||
	    ctnetlink_dump_master(skb, ct) < 0 ||
	    ctnetlink_dump_ct_seq_adj(skb, ct) < 0 ||
	    ctnetlink_dump_ct_synproxy(skb, ct) < 0)
		goto nla_put_failure;

	if (!test_bit(IPS_OFFLOAD_BIT, &ct->status) &&
	    (ctnetlink_dump_timeout(skb, ct) < 0 ||
	     ctnetlink_dump_protoinfo(skb, ct) < 0))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -1;
}