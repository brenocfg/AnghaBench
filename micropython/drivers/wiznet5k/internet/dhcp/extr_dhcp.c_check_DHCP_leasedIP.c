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
typedef  int int8_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_SOCKET ; 
 int /*<<< orphan*/  DHCP_allocated_ip ; 
 scalar_t__ SOCKERR_TIMEOUT ; 
 scalar_t__ dhcp_tick_1s ; 
 int getRCR () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  send_DHCP_DECLINE () ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setRCR (int) ; 

int8_t check_DHCP_leasedIP(void)
{
	uint8_t tmp;
	int32_t ret;

	//WIZchip RCR value changed for ARP Timeout count control
	tmp = getRCR();
	setRCR(0x03);

	// IP conflict detection : ARP request - ARP reply
	// Broadcasting ARP Request for check the IP conflict using UDP sendto() function
	ret = sendto(DHCP_SOCKET, (uint8_t *)"CHECK_IP_CONFLICT", 17, DHCP_allocated_ip, 5000);

	// RCR value restore
	setRCR(tmp);

	if(ret == SOCKERR_TIMEOUT) {
		// UDP send Timeout occurred : allocated IP address is unique, DHCP Success

#ifdef _DHCP_DEBUG_
		printf("\r\n> Check leased IP - OK\r\n");
#endif

		return 1;
	} else {
		// Received ARP reply or etc : IP address conflict occur, DHCP Failed
		send_DHCP_DECLINE();

		ret = dhcp_tick_1s;
		while((dhcp_tick_1s - ret) < 2) ;   // wait for 1s over; wait to complete to send DECLINE message;

		return 0;
	}
}