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
typedef  int bfa_port_speed_t ;

/* Variables and functions */
#define  BFA_PORT_SPEED_10GBPS 133 
#define  BFA_PORT_SPEED_16GBPS 132 
#define  BFA_PORT_SPEED_1GBPS 131 
#define  BFA_PORT_SPEED_2GBPS 130 
#define  BFA_PORT_SPEED_4GBPS 129 
#define  BFA_PORT_SPEED_8GBPS 128 
 int FDMI_TRANS_SPEED_10G ; 
 int FDMI_TRANS_SPEED_16G ; 
 int FDMI_TRANS_SPEED_4G ; 
 int FDMI_TRANS_SPEED_8G ; 
 int FDMI_TRANS_SPEED_UNKNOWN ; 

u32
bfa_fcs_fdmi_convert_speed(bfa_port_speed_t pport_speed)
{
	u32	ret;

	switch (pport_speed) {
	case BFA_PORT_SPEED_1GBPS:
	case BFA_PORT_SPEED_2GBPS:
		ret = pport_speed;
		break;

	case BFA_PORT_SPEED_4GBPS:
		ret = FDMI_TRANS_SPEED_4G;
		break;

	case BFA_PORT_SPEED_8GBPS:
		ret = FDMI_TRANS_SPEED_8G;
		break;

	case BFA_PORT_SPEED_10GBPS:
		ret = FDMI_TRANS_SPEED_10G;
		break;

	case BFA_PORT_SPEED_16GBPS:
		ret = FDMI_TRANS_SPEED_16G;
		break;

	default:
		ret = FDMI_TRANS_SPEED_UNKNOWN;
	}
	return ret;
}