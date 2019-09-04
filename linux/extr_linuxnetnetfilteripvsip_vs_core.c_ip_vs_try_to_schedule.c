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
struct netns_ipvs {int dummy; } ;
struct ip_vs_protocol {int /*<<< orphan*/  (* conn_schedule ) (struct netns_ipvs*,int,struct sk_buff*,struct ip_vs_proto_data*,int*,struct ip_vs_conn**,struct ip_vs_iphdr*) ;} ;
struct ip_vs_proto_data {struct ip_vs_protocol* pp; } ;
struct ip_vs_iphdr {int /*<<< orphan*/  off; scalar_t__ fragoffs; } ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_PKT (int,int,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int NF_ACCEPT ; 
 int /*<<< orphan*/  stub1 (struct netns_ipvs*,int,struct sk_buff*,struct ip_vs_proto_data*,int*,struct ip_vs_conn**,struct ip_vs_iphdr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int
ip_vs_try_to_schedule(struct netns_ipvs *ipvs, int af, struct sk_buff *skb,
		      struct ip_vs_proto_data *pd,
		      int *verdict, struct ip_vs_conn **cpp,
		      struct ip_vs_iphdr *iph)
{
	struct ip_vs_protocol *pp = pd->pp;

	if (!iph->fragoffs) {
		/* No (second) fragments need to enter here, as nf_defrag_ipv6
		 * replayed fragment zero will already have created the cp
		 */

		/* Schedule and create new connection entry into cpp */
		if (!pp->conn_schedule(ipvs, af, skb, pd, verdict, cpp, iph))
			return 0;
	}

	if (unlikely(!*cpp)) {
		/* sorry, all this trouble for a no-hit :) */
		IP_VS_DBG_PKT(12, af, pp, skb, iph->off,
			      "ip_vs_in: packet continues traversal as normal");

		/* Fragment couldn't be mapped to a conn entry */
		if (iph->fragoffs)
			IP_VS_DBG_PKT(7, af, pp, skb, iph->off,
				      "unhandled fragment");

		*verdict = NF_ACCEPT;
		return 0;
	}

	return 1;
}