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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 size_t CTA_ID ; 
 size_t CTA_TUPLE_ORIG ; 
 size_t CTA_TUPLE_REPLY ; 
 size_t CTA_ZONE ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IPS_OFFLOAD_BIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int ctnetlink_flush_conntrack (struct net*,struct nlattr const* const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ,struct nf_conntrack_zone*) ; 
 int ctnetlink_parse_zone (struct nlattr const* const,struct nf_conntrack_zone*) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,struct nf_conntrack_zone*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_delete (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctnetlink_del_conntrack(struct net *net, struct sock *ctnl,
				   struct sk_buff *skb,
				   const struct nlmsghdr *nlh,
				   const struct nlattr * const cda[],
				   struct netlink_ext_ack *extack)
{
	struct nf_conntrack_tuple_hash *h;
	struct nf_conntrack_tuple tuple;
	struct nf_conn *ct;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int8_t u3 = nfmsg->nfgen_family;
	struct nf_conntrack_zone zone;
	int err;

	err = ctnetlink_parse_zone(cda[CTA_ZONE], &zone);
	if (err < 0)
		return err;

	if (cda[CTA_TUPLE_ORIG])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_ORIG,
					    u3, &zone);
	else if (cda[CTA_TUPLE_REPLY])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_REPLY,
					    u3, &zone);
	else {
		return ctnetlink_flush_conntrack(net, cda,
						 NETLINK_CB(skb).portid,
						 nlmsg_report(nlh));
	}

	if (err < 0)
		return err;

	h = nf_conntrack_find_get(net, &zone, &tuple);
	if (!h)
		return -ENOENT;

	ct = nf_ct_tuplehash_to_ctrack(h);

	if (test_bit(IPS_OFFLOAD_BIT, &ct->status)) {
		nf_ct_put(ct);
		return -EBUSY;
	}

	if (cda[CTA_ID]) {
		u_int32_t id = ntohl(nla_get_be32(cda[CTA_ID]));
		if (id != (u32)(unsigned long)ct) {
			nf_ct_put(ct);
			return -ENOENT;
		}
	}

	nf_ct_delete(ct, NETLINK_CB(skb).portid, nlmsg_report(nlh));
	nf_ct_put(ct);

	return 0;
}