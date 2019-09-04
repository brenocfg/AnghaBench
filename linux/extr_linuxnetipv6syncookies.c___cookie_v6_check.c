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
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  seq; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 size_t check_tcp_syn_cookie (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int* msstab ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 

int __cookie_v6_check(const struct ipv6hdr *iph, const struct tcphdr *th,
		      __u32 cookie)
{
	__u32 seq = ntohl(th->seq) - 1;
	__u32 mssind = check_tcp_syn_cookie(cookie, &iph->saddr, &iph->daddr,
					    th->source, th->dest, seq);

	return mssind < ARRAY_SIZE(msstab) ? msstab[mssind] : 0;
}