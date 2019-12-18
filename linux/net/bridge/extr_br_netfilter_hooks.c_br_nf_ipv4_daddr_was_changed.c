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
struct nf_bridge_info {scalar_t__ ipv4_daddr; } ;
struct TYPE_2__ {scalar_t__ daddr; } ;

/* Variables and functions */
 TYPE_1__* ip_hdr (struct sk_buff const*) ; 

__attribute__((used)) static inline bool
br_nf_ipv4_daddr_was_changed(const struct sk_buff *skb,
			     const struct nf_bridge_info *nf_bridge)
{
	return ip_hdr(skb)->daddr != nf_bridge->ipv4_daddr;
}