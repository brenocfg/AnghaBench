#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dhcp; int /*<<< orphan*/ * dns; int /*<<< orphan*/ * sn; int /*<<< orphan*/  ip; int /*<<< orphan*/  gw; int /*<<< orphan*/  mac; } ;
typedef  TYPE_1__ wiz_NetInfo ;

/* Variables and functions */
 int /*<<< orphan*/  _DHCP_ ; 
 int /*<<< orphan*/ * _DNS_ ; 
 int /*<<< orphan*/ * _SUBN_ ; 
 int /*<<< orphan*/  setGAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSIPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSUBR (int /*<<< orphan*/ *) ; 

void wizchip_setnetinfo(wiz_NetInfo* pnetinfo)
{
   setSHAR(pnetinfo->mac);
   setGAR(pnetinfo->gw);
   setSUBR(pnetinfo->sn);
   setSIPR(pnetinfo->ip);
#if _WIZCHIP_ == 5200   // for W5200 ARP errata
   _SUBN_[0] = pnetinfo->sn[0];
   _SUBN_[1] = pnetinfo->sn[1];
   _SUBN_[2] = pnetinfo->sn[2];
   _SUBN_[3] = pnetinfo->sn[3];
#endif
   _DNS_[0] = pnetinfo->dns[0];
   _DNS_[1] = pnetinfo->dns[1];
   _DNS_[2] = pnetinfo->dns[2];
   _DNS_[3] = pnetinfo->dns[3];
   _DHCP_   = pnetinfo->dhcp;
}