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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
#define  AH_V4_FLOW 137 
#define  AH_V6_FLOW 136 
#define  ESP_V4_FLOW 135 
#define  ESP_V6_FLOW 134 
 int /*<<< orphan*/  IPPROTO_AH ; 
 int /*<<< orphan*/  IPPROTO_ESP ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static void niu_ethflow_to_l3proto(int flow_type, u8 *pid)
{
	switch (flow_type) {
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
		*pid = IPPROTO_TCP;
		break;
	case UDP_V4_FLOW:
	case UDP_V6_FLOW:
		*pid = IPPROTO_UDP;
		break;
	case SCTP_V4_FLOW:
	case SCTP_V6_FLOW:
		*pid = IPPROTO_SCTP;
		break;
	case AH_V4_FLOW:
	case AH_V6_FLOW:
		*pid = IPPROTO_AH;
		break;
	case ESP_V4_FLOW:
	case ESP_V6_FLOW:
		*pid = IPPROTO_ESP;
		break;
	default:
		*pid = 0;
		break;
	}
}