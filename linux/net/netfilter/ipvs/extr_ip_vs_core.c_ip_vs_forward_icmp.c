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
struct sk_buff {int dummy; } ;
struct nf_hook_state {int /*<<< orphan*/  hook; int /*<<< orphan*/  net; } ;
struct netns_ipvs {int /*<<< orphan*/  enable; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 unsigned int NF_ACCEPT ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 unsigned int ip_vs_in_icmp (struct netns_ipvs*,struct sk_buff*,int*,int /*<<< orphan*/ ) ; 
 struct netns_ipvs* net_ipvs (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_backup_only (struct netns_ipvs*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int
ip_vs_forward_icmp(void *priv, struct sk_buff *skb,
		   const struct nf_hook_state *state)
{
	int r;
	struct netns_ipvs *ipvs = net_ipvs(state->net);

	if (ip_hdr(skb)->protocol != IPPROTO_ICMP)
		return NF_ACCEPT;

	/* ipvs enabled in this netns ? */
	if (unlikely(sysctl_backup_only(ipvs) || !ipvs->enable))
		return NF_ACCEPT;

	return ip_vs_in_icmp(ipvs, skb, &r, state->hook);
}