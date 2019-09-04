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
typedef  int /*<<< orphan*/  RIP_MSG ;

/* Variables and functions */
 int* DHCP_CHADDR ; 
 int /*<<< orphan*/  DHCP_SOCKET ; 
 int DHCP_XID ; 
 int /*<<< orphan*/  STATE_DHCP_INIT ; 
 int /*<<< orphan*/  dhcp_state ; 
 int /*<<< orphan*/  getSHAR (int*) ; 
 int /*<<< orphan*/ * pDHCPMSG ; 
 int /*<<< orphan*/  reset_DHCP_timeout () ; 
 int /*<<< orphan*/  setGAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setSHAR (int*) ; 
 int /*<<< orphan*/  setSIPR (int /*<<< orphan*/ *) ; 

void DHCP_init(uint8_t s, uint8_t * buf)
{
   uint8_t zeroip[4] = {0,0,0,0};
   getSHAR(DHCP_CHADDR);
   if((DHCP_CHADDR[0] | DHCP_CHADDR[1]  | DHCP_CHADDR[2] | DHCP_CHADDR[3] | DHCP_CHADDR[4] | DHCP_CHADDR[5]) == 0x00)
   {
      // assign temporary mac address, you should be set SHAR before call this function.
      DHCP_CHADDR[0] = 0x00;
      DHCP_CHADDR[1] = 0x08;
      DHCP_CHADDR[2] = 0xdc;      
      DHCP_CHADDR[3] = 0x00;
      DHCP_CHADDR[4] = 0x00;
      DHCP_CHADDR[5] = 0x00; 
      setSHAR(DHCP_CHADDR);     
   }

	DHCP_SOCKET = s; // SOCK_DHCP
	pDHCPMSG = (RIP_MSG*)buf;
	DHCP_XID = 0x12345678;

	// WIZchip Netinfo Clear
	setSIPR(zeroip);
	setSIPR(zeroip);
	setGAR(zeroip);

	reset_DHCP_timeout();
	dhcp_state = STATE_DHCP_INIT;
}