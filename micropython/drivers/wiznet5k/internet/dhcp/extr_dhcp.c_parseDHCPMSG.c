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
typedef  int int8_t ;
struct TYPE_2__ {scalar_t__* chaddr; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 scalar_t__* DHCP_CHADDR ; 
 int DHCP_SERVER_PORT ; 
 int /*<<< orphan*/ * DHCP_SIP ; 
 int /*<<< orphan*/  DHCP_SOCKET ; 
 int /*<<< orphan*/ * DHCP_allocated_dns ; 
 int /*<<< orphan*/ * DHCP_allocated_gw ; 
 int /*<<< orphan*/ * DHCP_allocated_sn ; 
#define  dhcpIPaddrLeaseTime 135 
#define  dhcpMessageType 134 
#define  dhcpServerIdentifier 133 
 int dhcp_lease_time ; 
#define  dns 132 
#define  endOption 131 
 int getSn_RX_RSR (int /*<<< orphan*/ ) ; 
 TYPE_1__* pDHCPMSG ; 
#define  padOption 130 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 int recvfrom (int /*<<< orphan*/ ,int*,int,int*,int*) ; 
#define  routersOnSubnet 129 
#define  subnetMask 128 

int8_t parseDHCPMSG(void)
{
	uint8_t svr_addr[6];
	uint16_t  svr_port;
	uint16_t len;

	uint8_t * p;
	uint8_t * e;
	uint8_t type;
	uint8_t opt_len;
   
   if((len = getSn_RX_RSR(DHCP_SOCKET)) > 0)
   {
   	len = recvfrom(DHCP_SOCKET, (uint8_t *)pDHCPMSG, len, svr_addr, &svr_port);
   #ifdef _DHCP_DEBUG_   
      printf("DHCP message : %d.%d.%d.%d(%d) %d received. \r\n",svr_addr[0],svr_addr[1],svr_addr[2], svr_addr[3],svr_port, len);
   #endif   
   }
   else return 0;
	if (svr_port == DHCP_SERVER_PORT) {
      // compare mac address
		if ( (pDHCPMSG->chaddr[0] != DHCP_CHADDR[0]) || (pDHCPMSG->chaddr[1] != DHCP_CHADDR[1]) ||
		     (pDHCPMSG->chaddr[2] != DHCP_CHADDR[2]) || (pDHCPMSG->chaddr[3] != DHCP_CHADDR[3]) ||
		     (pDHCPMSG->chaddr[4] != DHCP_CHADDR[4]) || (pDHCPMSG->chaddr[5] != DHCP_CHADDR[5])   )
         return 0;
      type = 0;
		p = (uint8_t *)(&pDHCPMSG->op);
		p = p + 240;      // 240 = sizeof(RIP_MSG) + MAGIC_COOKIE size in RIP_MSG.opt - sizeof(RIP_MSG.opt)
		e = p + (len - 240);

		while ( p < e ) {

			switch ( *p ) {

   			case endOption :
   			   p = e;   // for break while(p < e)
   				break;
            case padOption :
   				p++;
   				break;
   			case dhcpMessageType :
   				p++;
   				p++;
   				type = *p++;
   				break;
   			case subnetMask :
   				p++;
   				p++;
   				DHCP_allocated_sn[0] = *p++;
   				DHCP_allocated_sn[1] = *p++;
   				DHCP_allocated_sn[2] = *p++;
   				DHCP_allocated_sn[3] = *p++;
   				break;
   			case routersOnSubnet :
   				p++;
   				opt_len = *p++;       
   				DHCP_allocated_gw[0] = *p++;
   				DHCP_allocated_gw[1] = *p++;
   				DHCP_allocated_gw[2] = *p++;
   				DHCP_allocated_gw[3] = *p++;
   				p = p + (opt_len - 4);
   				break;
   			case dns :
   				p++;                  
   				opt_len = *p++;       
   				DHCP_allocated_dns[0] = *p++;
   				DHCP_allocated_dns[1] = *p++;
   				DHCP_allocated_dns[2] = *p++;
   				DHCP_allocated_dns[3] = *p++;
   				p = p + (opt_len - 4);
   				break;
   			case dhcpIPaddrLeaseTime :
   				p++;
   				opt_len = *p++;
   				dhcp_lease_time  = *p++;
   				dhcp_lease_time  = (dhcp_lease_time << 8) + *p++;
   				dhcp_lease_time  = (dhcp_lease_time << 8) + *p++;
   				dhcp_lease_time  = (dhcp_lease_time << 8) + *p++;
            #ifdef _DHCP_DEBUG_  
                dhcp_lease_time = 10;
 			#endif
   				break;
   			case dhcpServerIdentifier :
   				p++;
   				opt_len = *p++;
   				DHCP_SIP[0] = *p++;
   				DHCP_SIP[1] = *p++;
   				DHCP_SIP[2] = *p++;
   				DHCP_SIP[3] = *p++;
   				break;
   			default :
   				p++;
   				opt_len = *p++;
   				p += opt_len;
   				break;
			} // switch
		} // while
	} // if
	return	type;
}