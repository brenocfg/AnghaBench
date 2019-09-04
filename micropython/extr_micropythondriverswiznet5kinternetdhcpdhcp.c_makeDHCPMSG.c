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
struct TYPE_2__ {int* OPT; scalar_t__* file; scalar_t__* sname; void** chaddr; scalar_t__* giaddr; scalar_t__* siaddr; scalar_t__* yiaddr; scalar_t__* ciaddr; int /*<<< orphan*/  flags; int /*<<< orphan*/  secs; int /*<<< orphan*/  xid; int /*<<< orphan*/  hops; int /*<<< orphan*/  hlen; int /*<<< orphan*/  htype; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_BOOTREQUEST ; 
 void** DHCP_CHADDR ; 
 int DHCP_FLAGSBROADCAST ; 
 int /*<<< orphan*/  DHCP_HLENETHERNET ; 
 int /*<<< orphan*/  DHCP_HOPS ; 
 int /*<<< orphan*/  DHCP_HTYPE10MB ; 
 int /*<<< orphan*/  DHCP_SECS ; 
 int DHCP_XID ; 
 int MAGIC_COOKIE ; 
 int /*<<< orphan*/  getSHAR (int*) ; 
 TYPE_1__* pDHCPMSG ; 

void makeDHCPMSG(void)
{
   uint8_t  bk_mac[6];
   uint8_t* ptmp;
   uint8_t  i;
   getSHAR(bk_mac);
	pDHCPMSG->op      = DHCP_BOOTREQUEST;
	pDHCPMSG->htype   = DHCP_HTYPE10MB;
	pDHCPMSG->hlen    = DHCP_HLENETHERNET;
	pDHCPMSG->hops    = DHCP_HOPS;
	ptmp              = (uint8_t*)(&pDHCPMSG->xid);
	*(ptmp+0)         = (uint8_t)((DHCP_XID & 0xFF000000) >> 24);
	*(ptmp+1)         = (uint8_t)((DHCP_XID & 0x00FF0000) >> 16);
   *(ptmp+2)         = (uint8_t)((DHCP_XID & 0x0000FF00) >>  8);
	*(ptmp+3)         = (uint8_t)((DHCP_XID & 0x000000FF) >>  0);   
	pDHCPMSG->secs    = DHCP_SECS;
	ptmp              = (uint8_t*)(&pDHCPMSG->flags);	
	*(ptmp+0)         = (uint8_t)((DHCP_FLAGSBROADCAST & 0xFF00) >> 8);
	*(ptmp+1)         = (uint8_t)((DHCP_FLAGSBROADCAST & 0x00FF) >> 0);

	pDHCPMSG->ciaddr[0] = 0;
	pDHCPMSG->ciaddr[1] = 0;
	pDHCPMSG->ciaddr[2] = 0;
	pDHCPMSG->ciaddr[3] = 0;

	pDHCPMSG->yiaddr[0] = 0;
	pDHCPMSG->yiaddr[1] = 0;
	pDHCPMSG->yiaddr[2] = 0;
	pDHCPMSG->yiaddr[3] = 0;

	pDHCPMSG->siaddr[0] = 0;
	pDHCPMSG->siaddr[1] = 0;
	pDHCPMSG->siaddr[2] = 0;
	pDHCPMSG->siaddr[3] = 0;

	pDHCPMSG->giaddr[0] = 0;
	pDHCPMSG->giaddr[1] = 0;
	pDHCPMSG->giaddr[2] = 0;
	pDHCPMSG->giaddr[3] = 0;

	pDHCPMSG->chaddr[0] = DHCP_CHADDR[0];
	pDHCPMSG->chaddr[1] = DHCP_CHADDR[1];
	pDHCPMSG->chaddr[2] = DHCP_CHADDR[2];
	pDHCPMSG->chaddr[3] = DHCP_CHADDR[3];
	pDHCPMSG->chaddr[4] = DHCP_CHADDR[4];
	pDHCPMSG->chaddr[5] = DHCP_CHADDR[5];

	for (i = 6; i < 16; i++)  pDHCPMSG->chaddr[i] = 0;
	for (i = 0; i < 64; i++)  pDHCPMSG->sname[i]  = 0;
	for (i = 0; i < 128; i++) pDHCPMSG->file[i]   = 0;

	// MAGIC_COOKIE
	pDHCPMSG->OPT[0] = (uint8_t)((MAGIC_COOKIE & 0xFF000000) >> 24);
	pDHCPMSG->OPT[1] = (uint8_t)((MAGIC_COOKIE & 0x00FF0000) >> 16);
	pDHCPMSG->OPT[2] = (uint8_t)((MAGIC_COOKIE & 0x0000FF00) >>  8);
	pDHCPMSG->OPT[3] = (uint8_t) (MAGIC_COOKIE & 0x000000FF) >>  0;
}