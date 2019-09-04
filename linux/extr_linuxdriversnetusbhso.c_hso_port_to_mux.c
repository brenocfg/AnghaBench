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

/* Variables and functions */
#define  HSO_PORT_APP 132 
#define  HSO_PORT_APP2 131 
#define  HSO_PORT_CONTROL 130 
#define  HSO_PORT_GPS 129 
 int HSO_PORT_MASK ; 
#define  HSO_PORT_PCSC 128 

__attribute__((used)) static u32 hso_port_to_mux(int port)
{
	u32 result;

	switch (port & HSO_PORT_MASK) {
	case HSO_PORT_CONTROL:
		result = 0x0;
		break;
	case HSO_PORT_APP:
		result = 0x1;
		break;
	case HSO_PORT_PCSC:
		result = 0x2;
		break;
	case HSO_PORT_GPS:
		result = 0x3;
		break;
	case HSO_PORT_APP2:
		result = 0x4;
		break;
	default:
		result = 0x0;
	}
	return result;
}