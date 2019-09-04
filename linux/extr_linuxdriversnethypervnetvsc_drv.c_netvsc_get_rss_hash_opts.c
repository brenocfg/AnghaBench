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
struct net_device_context {int l4_hash; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;

/* Variables and functions */
 int HV_TCP4_L4HASH ; 
 int HV_TCP6_L4HASH ; 
 int HV_UDP4_L4HASH ; 
 int HV_UDP6_L4HASH ; 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static int
netvsc_get_rss_hash_opts(struct net_device_context *ndc,
			 struct ethtool_rxnfc *info)
{
	const u32 l4_flag = RXH_L4_B_0_1 | RXH_L4_B_2_3;

	info->data = RXH_IP_SRC | RXH_IP_DST;

	switch (info->flow_type) {
	case TCP_V4_FLOW:
		if (ndc->l4_hash & HV_TCP4_L4HASH)
			info->data |= l4_flag;

		break;

	case TCP_V6_FLOW:
		if (ndc->l4_hash & HV_TCP6_L4HASH)
			info->data |= l4_flag;

		break;

	case UDP_V4_FLOW:
		if (ndc->l4_hash & HV_UDP4_L4HASH)
			info->data |= l4_flag;

		break;

	case UDP_V6_FLOW:
		if (ndc->l4_hash & HV_UDP6_L4HASH)
			info->data |= l4_flag;

		break;

	case IPV4_FLOW:
	case IPV6_FLOW:
		break;
	default:
		info->data = 0;
		break;
	}

	return 0;
}