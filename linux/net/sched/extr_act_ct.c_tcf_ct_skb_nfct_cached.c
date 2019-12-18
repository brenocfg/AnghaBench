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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  ct_general; int /*<<< orphan*/  ct_net; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ CTINFO2DIR (int) ; 
 scalar_t__ IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  IP_CT_UNTRACKED ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_put (int /*<<< orphan*/ *) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_kill (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* nf_ct_zone (struct nf_conn*) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tcf_ct_skb_nfct_cached(struct net *net, struct sk_buff *skb,
				   u16 zone_id, bool force)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		return false;
	if (!net_eq(net, read_pnet(&ct->ct_net)))
		return false;
	if (nf_ct_zone(ct)->id != zone_id)
		return false;

	/* Force conntrack entry direction. */
	if (force && CTINFO2DIR(ctinfo) != IP_CT_DIR_ORIGINAL) {
		if (nf_ct_is_confirmed(ct))
			nf_ct_kill(ct);

		nf_conntrack_put(&ct->ct_general);
		nf_ct_set(skb, NULL, IP_CT_UNTRACKED);

		return false;
	}

	return true;
}