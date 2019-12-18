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
struct sk_buff {int dummy; } ;
struct seg6_iptunnel_encap {int dummy; } ;
struct lwtunnel_state {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  SEG6_IPTUNNEL_SRH ; 
 scalar_t__ nla_put_srh (struct sk_buff*,int /*<<< orphan*/ ,struct seg6_iptunnel_encap*) ; 
 struct seg6_iptunnel_encap* seg6_encap_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static int seg6_fill_encap_info(struct sk_buff *skb,
				struct lwtunnel_state *lwtstate)
{
	struct seg6_iptunnel_encap *tuninfo = seg6_encap_lwtunnel(lwtstate);

	if (nla_put_srh(skb, SEG6_IPTUNNEL_SRH, tuninfo))
		return -EMSGSIZE;

	return 0;
}