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
struct tcphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  __cookie_v4_init_sequence (struct iphdr const*,struct tcphdr const*,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff const*) ; 

__u32 cookie_v4_init_sequence(const struct sk_buff *skb, __u16 *mssp)
{
	const struct iphdr *iph = ip_hdr(skb);
	const struct tcphdr *th = tcp_hdr(skb);

	return __cookie_v4_init_sequence(iph, th, mssp);
}