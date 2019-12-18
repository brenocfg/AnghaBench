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
typedef  int u32 ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
#define  ETH_P_8021AD 133 
#define  ETH_P_8021Q 132 
#define  ETH_P_IP 131 
#define  ETH_P_IPV6 130 
#define  ETH_P_MPLS_MC 129 
#define  ETH_P_MPLS_UC 128 
 int /*<<< orphan*/  PARSE_IP ; 
 int /*<<< orphan*/  PARSE_IPV6 ; 
 int /*<<< orphan*/  PARSE_MPLS ; 
 int /*<<< orphan*/  PARSE_VLAN ; 
 int /*<<< orphan*/  bpf_tail_call (struct __sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_table ; 

__attribute__((used)) static inline void parse_eth_proto(struct __sk_buff *skb, u32 proto)
{
	switch (proto) {
	case ETH_P_8021Q:
	case ETH_P_8021AD:
		bpf_tail_call(skb, &jmp_table, PARSE_VLAN);
		break;
	case ETH_P_MPLS_UC:
	case ETH_P_MPLS_MC:
		bpf_tail_call(skb, &jmp_table, PARSE_MPLS);
		break;
	case ETH_P_IP:
		bpf_tail_call(skb, &jmp_table, PARSE_IP);
		break;
	case ETH_P_IPV6:
		bpf_tail_call(skb, &jmp_table, PARSE_IPV6);
		break;
	}
}