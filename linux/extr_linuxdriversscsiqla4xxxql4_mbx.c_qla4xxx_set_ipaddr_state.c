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
typedef  int uint8_t ;

/* Variables and functions */
#define  IP_ADDRSTATE_ACQUIRING 134 
#define  IP_ADDRSTATE_DEPRICATED 133 
#define  IP_ADDRSTATE_DISABLING 132 
#define  IP_ADDRSTATE_INVALID 131 
#define  IP_ADDRSTATE_PREFERRED 130 
#define  IP_ADDRSTATE_TENTATIVE 129 
#define  IP_ADDRSTATE_UNCONFIGURED 128 
 int ISCSI_IPDDRESS_STATE_ACQUIRING ; 
 int ISCSI_IPDDRESS_STATE_DEPRECATED ; 
 int ISCSI_IPDDRESS_STATE_DISABLING ; 
 int ISCSI_IPDDRESS_STATE_INVALID ; 
 int ISCSI_IPDDRESS_STATE_TENTATIVE ; 
 int ISCSI_IPDDRESS_STATE_UNCONFIGURED ; 
 int ISCSI_IPDDRESS_STATE_VALID ; 

uint8_t qla4xxx_set_ipaddr_state(uint8_t fw_ipaddr_state)
{
	uint8_t ipaddr_state;

	switch (fw_ipaddr_state) {
	case IP_ADDRSTATE_UNCONFIGURED:
		ipaddr_state = ISCSI_IPDDRESS_STATE_UNCONFIGURED;
		break;
	case IP_ADDRSTATE_INVALID:
		ipaddr_state = ISCSI_IPDDRESS_STATE_INVALID;
		break;
	case IP_ADDRSTATE_ACQUIRING:
		ipaddr_state = ISCSI_IPDDRESS_STATE_ACQUIRING;
		break;
	case IP_ADDRSTATE_TENTATIVE:
		ipaddr_state = ISCSI_IPDDRESS_STATE_TENTATIVE;
		break;
	case IP_ADDRSTATE_DEPRICATED:
		ipaddr_state = ISCSI_IPDDRESS_STATE_DEPRECATED;
		break;
	case IP_ADDRSTATE_PREFERRED:
		ipaddr_state = ISCSI_IPDDRESS_STATE_VALID;
		break;
	case IP_ADDRSTATE_DISABLING:
		ipaddr_state = ISCSI_IPDDRESS_STATE_DISABLING;
		break;
	default:
		ipaddr_state = ISCSI_IPDDRESS_STATE_UNCONFIGURED;
	}
	return ipaddr_state;
}