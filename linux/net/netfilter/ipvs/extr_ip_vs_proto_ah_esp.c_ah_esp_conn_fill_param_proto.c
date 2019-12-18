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
struct netns_ipvs {int dummy; } ;
struct ip_vs_iphdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ip_vs_conn_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PORT_ISAKMP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param (struct netns_ipvs*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  ip_vs_iph_inverse (struct ip_vs_iphdr const*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void
ah_esp_conn_fill_param_proto(struct netns_ipvs *ipvs, int af,
			     const struct ip_vs_iphdr *iph,
			     struct ip_vs_conn_param *p)
{
	if (likely(!ip_vs_iph_inverse(iph)))
		ip_vs_conn_fill_param(ipvs, af, IPPROTO_UDP,
				      &iph->saddr, htons(PORT_ISAKMP),
				      &iph->daddr, htons(PORT_ISAKMP), p);
	else
		ip_vs_conn_fill_param(ipvs, af, IPPROTO_UDP,
				      &iph->daddr, htons(PORT_ISAKMP),
				      &iph->saddr, htons(PORT_ISAKMP), p);
}