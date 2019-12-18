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
union nf_inet_addr {int /*<<< orphan*/  in6; int /*<<< orphan*/  ip; } ;
typedef  scalar_t__ u_int8_t ;
struct xt_recent_mtinfo_v1 {int invert; scalar_t__ side; int check_set; unsigned long seconds; unsigned int hit_count; int /*<<< orphan*/  name; } ;
struct xt_action_param {int hotdrop; struct xt_recent_mtinfo_v1* matchinfo; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct recent_table {int /*<<< orphan*/  mask; } ;
struct recent_net {int dummy; } ;
struct recent_entry {unsigned int nstamps; scalar_t__ ttl; int /*<<< orphan*/ * stamps; } ;
struct net {int dummy; } ;
struct ipv6hdr {scalar_t__ hop_limit; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct iphdr {scalar_t__ ttl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ NFPROTO_IPV4 ; 
 int XT_RECENT_CHECK ; 
 scalar_t__ XT_RECENT_DEST ; 
 int XT_RECENT_REAP ; 
 int XT_RECENT_REMOVE ; 
 int XT_RECENT_SET ; 
 int XT_RECENT_TTL ; 
 int XT_RECENT_UPDATE ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_inet_addr_mask (union nf_inet_addr*,union nf_inet_addr*,int /*<<< orphan*/ *) ; 
 struct recent_entry* recent_entry_init (struct recent_table*,union nf_inet_addr*,scalar_t__,scalar_t__) ; 
 struct recent_entry* recent_entry_lookup (struct recent_table*,union nf_inet_addr*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  recent_entry_reap (struct recent_table*,unsigned long) ; 
 int /*<<< orphan*/  recent_entry_remove (struct recent_table*,struct recent_entry*) ; 
 int /*<<< orphan*/  recent_entry_update (struct recent_table*,struct recent_entry*) ; 
 int /*<<< orphan*/  recent_lock ; 
 struct recent_net* recent_pernet (struct net*) ; 
 struct recent_table* recent_table_lookup (struct recent_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ xt_family (struct xt_action_param*) ; 
 struct net* xt_net (struct xt_action_param*) ; 
 int /*<<< orphan*/ * xt_out (struct xt_action_param*) ; 

__attribute__((used)) static bool
recent_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	struct net *net = xt_net(par);
	struct recent_net *recent_net = recent_pernet(net);
	const struct xt_recent_mtinfo_v1 *info = par->matchinfo;
	struct recent_table *t;
	struct recent_entry *e;
	union nf_inet_addr addr = {}, addr_mask;
	u_int8_t ttl;
	bool ret = info->invert;

	if (xt_family(par) == NFPROTO_IPV4) {
		const struct iphdr *iph = ip_hdr(skb);

		if (info->side == XT_RECENT_DEST)
			addr.ip = iph->daddr;
		else
			addr.ip = iph->saddr;

		ttl = iph->ttl;
	} else {
		const struct ipv6hdr *iph = ipv6_hdr(skb);

		if (info->side == XT_RECENT_DEST)
			memcpy(&addr.in6, &iph->daddr, sizeof(addr.in6));
		else
			memcpy(&addr.in6, &iph->saddr, sizeof(addr.in6));

		ttl = iph->hop_limit;
	}

	/* use TTL as seen before forwarding */
	if (xt_out(par) != NULL &&
	    (!skb->sk || !net_eq(net, sock_net(skb->sk))))
		ttl++;

	spin_lock_bh(&recent_lock);
	t = recent_table_lookup(recent_net, info->name);

	nf_inet_addr_mask(&addr, &addr_mask, &t->mask);

	e = recent_entry_lookup(t, &addr_mask, xt_family(par),
				(info->check_set & XT_RECENT_TTL) ? ttl : 0);
	if (e == NULL) {
		if (!(info->check_set & XT_RECENT_SET))
			goto out;
		e = recent_entry_init(t, &addr_mask, xt_family(par), ttl);
		if (e == NULL)
			par->hotdrop = true;
		ret = !ret;
		goto out;
	}

	if (info->check_set & XT_RECENT_SET)
		ret = !ret;
	else if (info->check_set & XT_RECENT_REMOVE) {
		recent_entry_remove(t, e);
		ret = !ret;
	} else if (info->check_set & (XT_RECENT_CHECK | XT_RECENT_UPDATE)) {
		unsigned long time = jiffies - info->seconds * HZ;
		unsigned int i, hits = 0;

		for (i = 0; i < e->nstamps; i++) {
			if (info->seconds && time_after(time, e->stamps[i]))
				continue;
			if (!info->hit_count || ++hits >= info->hit_count) {
				ret = !ret;
				break;
			}
		}

		/* info->seconds must be non-zero */
		if (info->check_set & XT_RECENT_REAP)
			recent_entry_reap(t, time);
	}

	if (info->check_set & XT_RECENT_SET ||
	    (info->check_set & XT_RECENT_UPDATE && ret)) {
		recent_entry_update(t, e);
		e->ttl = ttl;
	}
out:
	spin_unlock_bh(&recent_lock);
	return ret;
}