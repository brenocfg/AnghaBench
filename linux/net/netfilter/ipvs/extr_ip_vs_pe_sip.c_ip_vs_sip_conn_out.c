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
struct ip_vs_service {int dummy; } ;
struct ip_vs_iphdr {scalar_t__ protocol; } ;
struct ip_vs_dest {int dummy; } ;
struct ip_vs_conn {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 struct ip_vs_conn* ip_vs_new_conn_out (struct ip_vs_service*,struct ip_vs_dest*,struct sk_buff*,struct ip_vs_iphdr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static struct ip_vs_conn *
ip_vs_sip_conn_out(struct ip_vs_service *svc,
		   struct ip_vs_dest *dest,
		   struct sk_buff *skb,
		   const struct ip_vs_iphdr *iph,
		   __be16 dport,
		   __be16 cport)
{
	if (likely(iph->protocol == IPPROTO_UDP))
		return ip_vs_new_conn_out(svc, dest, skb, iph, dport, cport);
	/* currently no need to handle other than UDP */
	return NULL;
}