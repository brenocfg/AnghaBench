#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int* OPT; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void** DHCP_CHADDR ; 
 int DHCP_DECLINE ; 
 int DHCP_FLAGSUNICAST ; 
 int /*<<< orphan*/  DHCP_SERVER_PORT ; 
 void** DHCP_SIP ; 
 int /*<<< orphan*/  DHCP_SOCKET ; 
 void** DHCP_allocated_ip ; 
 int OPT_SIZE ; 
 int /*<<< orphan*/  RIP_MSG_SIZE ; 
 int dhcpClientIdentifier ; 
 int dhcpMessageType ; 
 int dhcpRequestedIPaddr ; 
 int dhcpServerIdentifier ; 
 int endOption ; 
 int /*<<< orphan*/  makeDHCPMSG () ; 
 TYPE_1__* pDHCPMSG ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sendto (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

void send_DHCP_DECLINE(void)
{
	int i;
	uint8_t ip[4];
	uint16_t k = 0;
	
	makeDHCPMSG();

   k = 4;      // because MAGIC_COOKIE already made by makeDHCPMSG()
   
	*((uint8_t*)(&pDHCPMSG->flags))   = ((DHCP_FLAGSUNICAST & 0xFF00)>> 8);
	*((uint8_t*)(&pDHCPMSG->flags)+1) = (DHCP_FLAGSUNICAST & 0x00FF);

	// Option Request Param.
	pDHCPMSG->OPT[k++] = dhcpMessageType;
	pDHCPMSG->OPT[k++] = 0x01;
	pDHCPMSG->OPT[k++] = DHCP_DECLINE;

	pDHCPMSG->OPT[k++] = dhcpClientIdentifier;
	pDHCPMSG->OPT[k++] = 0x07;
	pDHCPMSG->OPT[k++] = 0x01;
	pDHCPMSG->OPT[k++] = DHCP_CHADDR[0];
	pDHCPMSG->OPT[k++] = DHCP_CHADDR[1];
	pDHCPMSG->OPT[k++] = DHCP_CHADDR[2];
	pDHCPMSG->OPT[k++] = DHCP_CHADDR[3];
	pDHCPMSG->OPT[k++] = DHCP_CHADDR[4];
	pDHCPMSG->OPT[k++] = DHCP_CHADDR[5];

	pDHCPMSG->OPT[k++] = dhcpRequestedIPaddr;
	pDHCPMSG->OPT[k++] = 0x04;
	pDHCPMSG->OPT[k++] = DHCP_allocated_ip[0];
	pDHCPMSG->OPT[k++] = DHCP_allocated_ip[1];
	pDHCPMSG->OPT[k++] = DHCP_allocated_ip[2];
	pDHCPMSG->OPT[k++] = DHCP_allocated_ip[3];

	pDHCPMSG->OPT[k++] = dhcpServerIdentifier;
	pDHCPMSG->OPT[k++] = 0x04;
	pDHCPMSG->OPT[k++] = DHCP_SIP[0];
	pDHCPMSG->OPT[k++] = DHCP_SIP[1];
	pDHCPMSG->OPT[k++] = DHCP_SIP[2];
	pDHCPMSG->OPT[k++] = DHCP_SIP[3];

	pDHCPMSG->OPT[k++] = endOption;

	for (i = k; i < OPT_SIZE; i++) pDHCPMSG->OPT[i] = 0;

	//send broadcasting packet
	ip[0] = 0xFF;
	ip[1] = 0xFF;
	ip[2] = 0xFF;
	ip[3] = 0xFF;

#ifdef _DHCP_DEBUG_
	printf("\r\n> Send DHCP_DECLINE\r\n");
#endif

	sendto(DHCP_SOCKET, (uint8_t *)pDHCPMSG, RIP_MSG_SIZE, ip, DHCP_SERVER_PORT);
}