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
struct ip_vs_proto_data {int dummy; } ;
struct ip_vs_iphdr {int dummy; } ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int NF_ACCEPT ; 

__attribute__((used)) static int
ah_esp_conn_schedule(struct netns_ipvs *ipvs, int af, struct sk_buff *skb,
		     struct ip_vs_proto_data *pd,
		     int *verdict, struct ip_vs_conn **cpp,
		     struct ip_vs_iphdr *iph)
{
	/*
	 * AH/ESP is only related traffic. Pass the packet to IP stack.
	 */
	*verdict = NF_ACCEPT;
	return 0;
}