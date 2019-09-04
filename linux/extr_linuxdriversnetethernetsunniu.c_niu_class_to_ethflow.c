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
typedef  int u64 ;

/* Variables and functions */
 int AH_V4_FLOW ; 
 int AH_V6_FLOW ; 
#define  CLASS_CODE_AH_ESP_IPV4 139 
#define  CLASS_CODE_AH_ESP_IPV6 138 
#define  CLASS_CODE_SCTP_IPV4 137 
#define  CLASS_CODE_SCTP_IPV6 136 
#define  CLASS_CODE_TCP_IPV4 135 
#define  CLASS_CODE_TCP_IPV6 134 
#define  CLASS_CODE_UDP_IPV4 133 
#define  CLASS_CODE_UDP_IPV6 132 
#define  CLASS_CODE_USER_PROG1 131 
#define  CLASS_CODE_USER_PROG2 130 
#define  CLASS_CODE_USER_PROG3 129 
#define  CLASS_CODE_USER_PROG4 128 
 int EINVAL ; 
 int IP_USER_FLOW ; 
 int SCTP_V4_FLOW ; 
 int SCTP_V6_FLOW ; 
 int TCP_V4_FLOW ; 
 int TCP_V6_FLOW ; 
 int UDP_V4_FLOW ; 
 int UDP_V6_FLOW ; 

__attribute__((used)) static int niu_class_to_ethflow(u64 class, int *flow_type)
{
	switch (class) {
	case CLASS_CODE_TCP_IPV4:
		*flow_type = TCP_V4_FLOW;
		break;
	case CLASS_CODE_UDP_IPV4:
		*flow_type = UDP_V4_FLOW;
		break;
	case CLASS_CODE_AH_ESP_IPV4:
		*flow_type = AH_V4_FLOW;
		break;
	case CLASS_CODE_SCTP_IPV4:
		*flow_type = SCTP_V4_FLOW;
		break;
	case CLASS_CODE_TCP_IPV6:
		*flow_type = TCP_V6_FLOW;
		break;
	case CLASS_CODE_UDP_IPV6:
		*flow_type = UDP_V6_FLOW;
		break;
	case CLASS_CODE_AH_ESP_IPV6:
		*flow_type = AH_V6_FLOW;
		break;
	case CLASS_CODE_SCTP_IPV6:
		*flow_type = SCTP_V6_FLOW;
		break;
	case CLASS_CODE_USER_PROG1:
	case CLASS_CODE_USER_PROG2:
	case CLASS_CODE_USER_PROG3:
	case CLASS_CODE_USER_PROG4:
		*flow_type = IP_USER_FLOW;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}