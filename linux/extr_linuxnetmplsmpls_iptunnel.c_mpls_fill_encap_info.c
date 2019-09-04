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
struct mpls_iptunnel_encap {scalar_t__ ttl_propagate; int /*<<< orphan*/  default_ttl; int /*<<< orphan*/  label; int /*<<< orphan*/  labels; } ;
struct lwtunnel_state {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  MPLS_IPTUNNEL_DST ; 
 int /*<<< orphan*/  MPLS_IPTUNNEL_TTL ; 
 scalar_t__ MPLS_TTL_PROP_DEFAULT ; 
 struct mpls_iptunnel_encap* mpls_lwtunnel_encap (struct lwtunnel_state*) ; 
 scalar_t__ nla_put_labels (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpls_fill_encap_info(struct sk_buff *skb,
				struct lwtunnel_state *lwtstate)
{
	struct mpls_iptunnel_encap *tun_encap_info;

	tun_encap_info = mpls_lwtunnel_encap(lwtstate);

	if (nla_put_labels(skb, MPLS_IPTUNNEL_DST, tun_encap_info->labels,
			   tun_encap_info->label))
		goto nla_put_failure;

	if (tun_encap_info->ttl_propagate != MPLS_TTL_PROP_DEFAULT &&
	    nla_put_u8(skb, MPLS_IPTUNNEL_TTL, tun_encap_info->default_ttl))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}