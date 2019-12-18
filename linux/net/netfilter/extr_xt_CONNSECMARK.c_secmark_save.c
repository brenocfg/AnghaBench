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
struct sk_buff {scalar_t__ secmark; } ;
struct nf_conn {scalar_t__ secmark; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_SECMARK ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 

__attribute__((used)) static void secmark_save(const struct sk_buff *skb)
{
	if (skb->secmark) {
		struct nf_conn *ct;
		enum ip_conntrack_info ctinfo;

		ct = nf_ct_get(skb, &ctinfo);
		if (ct && !ct->secmark) {
			ct->secmark = skb->secmark;
			nf_conntrack_event_cache(IPCT_SECMARK, ct);
		}
	}
}