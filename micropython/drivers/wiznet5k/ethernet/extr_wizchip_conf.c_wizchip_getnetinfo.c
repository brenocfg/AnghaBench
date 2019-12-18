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
struct TYPE_3__ {int /*<<< orphan*/  dhcp; void** dns; void** sn; int /*<<< orphan*/  ip; int /*<<< orphan*/  gw; int /*<<< orphan*/  mac; } ;
typedef  TYPE_1__ wiz_NetInfo ;

/* Variables and functions */
 int /*<<< orphan*/  _DHCP_ ; 
 void** _DNS_ ; 
 void** _SUBN_ ; 
 int /*<<< orphan*/  getGAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getSHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getSIPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getSUBR (void**) ; 

void wizchip_getnetinfo(wiz_NetInfo* pnetinfo)
{
   getSHAR(pnetinfo->mac);
   getGAR(pnetinfo->gw);
   getSUBR(pnetinfo->sn);
   getSIPR(pnetinfo->ip);
#if _WIZCHIP_ == 5200   // for W5200 ARP errata
   pnetinfo->sn[0] = _SUBN_[0];
   pnetinfo->sn[1] = _SUBN_[1];
   pnetinfo->sn[2] = _SUBN_[2];
   pnetinfo->sn[3] = _SUBN_[3];
#endif
   pnetinfo->dns[0]= _DNS_[0];
   pnetinfo->dns[1]= _DNS_[1];
   pnetinfo->dns[2]= _DNS_[2];
   pnetinfo->dns[3]= _DNS_[3];
   pnetinfo->dhcp  = _DHCP_;
}