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
struct xt_connmark_mtinfo1 {int mask; int mark; int invert; } ;
struct xt_action_param {struct xt_connmark_mtinfo1* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct nf_conn {int mark; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 

__attribute__((used)) static bool
connmark_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_connmark_mtinfo1 *info = par->matchinfo;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return false;

	return ((ct->mark & info->mask) == info->mark) ^ info->invert;
}