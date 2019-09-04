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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DHCP_allocated_ip ; 

void getIPfromDHCP(uint8_t* ip)
{
	ip[0] = DHCP_allocated_ip[0];
	ip[1] = DHCP_allocated_ip[1];
	ip[2] = DHCP_allocated_ip[2];	
	ip[3] = DHCP_allocated_ip[3];
}