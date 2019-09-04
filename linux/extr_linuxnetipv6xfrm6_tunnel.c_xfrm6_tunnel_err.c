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
struct sk_buff {int dummy; } ;
struct inet6_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  ICMPV6_ADDR_UNREACH 141 
#define  ICMPV6_ADM_PROHIBITED 140 
#define  ICMPV6_DEST_UNREACH 139 
#define  ICMPV6_EXC_FRAGTIME 138 
#define  ICMPV6_EXC_HOPLIMIT 137 
#define  ICMPV6_HDR_FIELD 136 
#define  ICMPV6_NOROUTE 135 
#define  ICMPV6_NOT_NEIGHBOUR 134 
#define  ICMPV6_PARAMPROB 133 
#define  ICMPV6_PKT_TOOBIG 132 
#define  ICMPV6_PORT_UNREACH 131 
#define  ICMPV6_TIME_EXCEED 130 
#define  ICMPV6_UNK_NEXTHDR 129 
#define  ICMPV6_UNK_OPTION 128 

__attribute__((used)) static int xfrm6_tunnel_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
			    u8 type, u8 code, int offset, __be32 info)
{
	/* xfrm6_tunnel native err handling */
	switch (type) {
	case ICMPV6_DEST_UNREACH:
		switch (code) {
		case ICMPV6_NOROUTE:
		case ICMPV6_ADM_PROHIBITED:
		case ICMPV6_NOT_NEIGHBOUR:
		case ICMPV6_ADDR_UNREACH:
		case ICMPV6_PORT_UNREACH:
		default:
			break;
		}
		break;
	case ICMPV6_PKT_TOOBIG:
		break;
	case ICMPV6_TIME_EXCEED:
		switch (code) {
		case ICMPV6_EXC_HOPLIMIT:
			break;
		case ICMPV6_EXC_FRAGTIME:
		default:
			break;
		}
		break;
	case ICMPV6_PARAMPROB:
		switch (code) {
		case ICMPV6_HDR_FIELD: break;
		case ICMPV6_UNK_NEXTHDR: break;
		case ICMPV6_UNK_OPTION: break;
		}
		break;
	default:
		break;
	}

	return 0;
}