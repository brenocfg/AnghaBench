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
typedef  int u8 ;
struct xt_action_param {int /*<<< orphan*/  thoff; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int protocol; } ;

/* Variables and functions */
#define  IPPROTO_L2TP 129 
#define  IPPROTO_UDP 128 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 int l2tp_ip_mt (struct sk_buff const*,struct xt_action_param*,int /*<<< orphan*/ ) ; 
 int l2tp_udp_mt (struct sk_buff const*,struct xt_action_param*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool l2tp_mt4(const struct sk_buff *skb, struct xt_action_param *par)
{
	struct iphdr *iph = ip_hdr(skb);
	u8 ipproto = iph->protocol;

	/* l2tp_mt_check4 already restricts the transport protocol */
	switch (ipproto) {
	case IPPROTO_UDP:
		return l2tp_udp_mt(skb, par, par->thoff);
	case IPPROTO_L2TP:
		return l2tp_ip_mt(skb, par, par->thoff);
	}

	return false;
}