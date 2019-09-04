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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct TYPE_3__ {scalar_t__ protonum; } ;
struct nf_conntrack_tuple {TYPE_1__ dst; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_events { ____Placeholder_ip_conntrack_events } ip_conntrack_events ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 size_t CTA_LABELS ; 
 size_t CTA_TUPLE_ORIG ; 
 size_t CTA_TUPLE_REPLY ; 
 size_t CTA_ZONE ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int IPCT_ASSURED ; 
 int IPCT_HELPER ; 
 int IPCT_LABEL ; 
 int IPCT_MARK ; 
 int IPCT_NEW ; 
 int IPCT_PROTOINFO ; 
 int IPCT_RELATED ; 
 int IPCT_REPLY ; 
 int IPCT_SEQADJ ; 
 int IPCT_SYNPROXY ; 
 int /*<<< orphan*/  IPS_EXPECTED_BIT ; 
 scalar_t__ IS_ERR (struct nf_conn*) ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 int PTR_ERR (struct nf_conn*) ; 
 scalar_t__ ctnetlink_attach_labels (struct nf_conn*,struct nlattr const* const*) ; 
 int ctnetlink_change_conntrack (struct nf_conn*,struct nlattr const* const*) ; 
 struct nf_conn* ctnetlink_create_conntrack (struct net*,struct nf_conntrack_zone*,struct nlattr const* const*,struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,int /*<<< orphan*/ ) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ,struct nf_conntrack_zone*) ; 
 int ctnetlink_parse_zone (struct nlattr const* const,struct nf_conntrack_zone*) ; 
 int /*<<< orphan*/  nf_conntrack_eventmask_report (int,struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_zone*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctnetlink_new_conntrack(struct net *net, struct sock *ctnl,
				   struct sk_buff *skb,
				   const struct nlmsghdr *nlh,
				   const struct nlattr * const cda[],
				   struct netlink_ext_ack *extack)
{
	struct nf_conntrack_tuple otuple, rtuple;
	struct nf_conntrack_tuple_hash *h = NULL;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	struct nf_conn *ct;
	u_int8_t u3 = nfmsg->nfgen_family;
	struct nf_conntrack_zone zone;
	int err;

	err = ctnetlink_parse_zone(cda[CTA_ZONE], &zone);
	if (err < 0)
		return err;

	if (cda[CTA_TUPLE_ORIG]) {
		err = ctnetlink_parse_tuple(cda, &otuple, CTA_TUPLE_ORIG,
					    u3, &zone);
		if (err < 0)
			return err;
	}

	if (cda[CTA_TUPLE_REPLY]) {
		err = ctnetlink_parse_tuple(cda, &rtuple, CTA_TUPLE_REPLY,
					    u3, &zone);
		if (err < 0)
			return err;
	}

	if (cda[CTA_TUPLE_ORIG])
		h = nf_conntrack_find_get(net, &zone, &otuple);
	else if (cda[CTA_TUPLE_REPLY])
		h = nf_conntrack_find_get(net, &zone, &rtuple);

	if (h == NULL) {
		err = -ENOENT;
		if (nlh->nlmsg_flags & NLM_F_CREATE) {
			enum ip_conntrack_events events;

			if (!cda[CTA_TUPLE_ORIG] || !cda[CTA_TUPLE_REPLY])
				return -EINVAL;
			if (otuple.dst.protonum != rtuple.dst.protonum)
				return -EINVAL;

			ct = ctnetlink_create_conntrack(net, &zone, cda, &otuple,
							&rtuple, u3);
			if (IS_ERR(ct))
				return PTR_ERR(ct);

			err = 0;
			if (test_bit(IPS_EXPECTED_BIT, &ct->status))
				events = 1 << IPCT_RELATED;
			else
				events = 1 << IPCT_NEW;

			if (cda[CTA_LABELS] &&
			    ctnetlink_attach_labels(ct, cda) == 0)
				events |= (1 << IPCT_LABEL);

			nf_conntrack_eventmask_report((1 << IPCT_REPLY) |
						      (1 << IPCT_ASSURED) |
						      (1 << IPCT_HELPER) |
						      (1 << IPCT_PROTOINFO) |
						      (1 << IPCT_SEQADJ) |
						      (1 << IPCT_MARK) |
						      (1 << IPCT_SYNPROXY) |
						      events,
						      ct, NETLINK_CB(skb).portid,
						      nlmsg_report(nlh));
			nf_ct_put(ct);
		}

		return err;
	}
	/* implicit 'else' */

	err = -EEXIST;
	ct = nf_ct_tuplehash_to_ctrack(h);
	if (!(nlh->nlmsg_flags & NLM_F_EXCL)) {
		err = ctnetlink_change_conntrack(ct, cda);
		if (err == 0) {
			nf_conntrack_eventmask_report((1 << IPCT_REPLY) |
						      (1 << IPCT_ASSURED) |
						      (1 << IPCT_HELPER) |
						      (1 << IPCT_LABEL) |
						      (1 << IPCT_PROTOINFO) |
						      (1 << IPCT_SEQADJ) |
						      (1 << IPCT_MARK) |
						      (1 << IPCT_SYNPROXY),
						      ct, NETLINK_CB(skb).portid,
						      nlmsg_report(nlh));
		}
	}

	nf_ct_put(ct);
	return err;
}