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
struct xt_action_param {int dummy; } ;
struct tcphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int ihl; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  check; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  PF_INET ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  csum_replace2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int tcpmss_mangle_packet (struct sk_buff*,struct xt_action_param const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned int
tcpmss_tg4(struct sk_buff *skb, const struct xt_action_param *par)
{
	struct iphdr *iph = ip_hdr(skb);
	__be16 newlen;
	int ret;

	ret = tcpmss_mangle_packet(skb, par,
				   PF_INET,
				   iph->ihl * 4,
				   sizeof(*iph) + sizeof(struct tcphdr));
	if (ret < 0)
		return NF_DROP;
	if (ret > 0) {
		iph = ip_hdr(skb);
		newlen = htons(ntohs(iph->tot_len) + ret);
		csum_replace2(&iph->check, iph->tot_len, newlen);
		iph->tot_len = newlen;
	}
	return XT_CONTINUE;
}