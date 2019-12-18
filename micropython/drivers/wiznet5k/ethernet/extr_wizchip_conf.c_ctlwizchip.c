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
typedef  int /*<<< orphan*/  wiz_PhyConf ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  intr_kind ;
typedef  int int8_t ;
typedef  int ctlwizchip_type ;
struct TYPE_2__ {int /*<<< orphan*/ * id; } ;

/* Variables and functions */
#define  CW_CLR_INTERRUPT 143 
#define  CW_GET_ID 142 
#define  CW_GET_INTERRUPT 141 
#define  CW_GET_INTRMASK 140 
#define  CW_GET_INTRTIME 139 
#define  CW_GET_PHYCONF 138 
#define  CW_GET_PHYLINK 137 
#define  CW_GET_PHYPOWMODE 136 
#define  CW_GET_PHYSTATUS 135 
#define  CW_INIT_WIZCHIP 134 
#define  CW_RESET_PHY 133 
#define  CW_RESET_WIZCHIP 132 
#define  CW_SET_INTRMASK 131 
#define  CW_SET_INTRTIME 130 
#define  CW_SET_PHYCONF 129 
#define  CW_SET_PHYPOWMODE 128 
 TYPE_1__ WIZCHIP ; 
 int /*<<< orphan*/  _WIZCHIP_SOCK_NUM_ ; 
 int /*<<< orphan*/  getINTLEVEL () ; 
 int /*<<< orphan*/  setINTLEVEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wizchip_clrinterrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wizchip_getinterrupt () ; 
 int /*<<< orphan*/  wizchip_getinterruptmask () ; 
 int wizchip_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wizchip_setinterruptmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wizchip_sw_reset () ; 
 int /*<<< orphan*/  wizphy_getphyconf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wizphy_getphylink () ; 
 int /*<<< orphan*/  wizphy_getphypmode () ; 
 int /*<<< orphan*/  wizphy_reset () ; 
 int /*<<< orphan*/  wizphy_setphyconf (int /*<<< orphan*/ *) ; 
 int wizphy_setphypmode (int /*<<< orphan*/ ) ; 

int8_t ctlwizchip(ctlwizchip_type cwtype, void* arg)
{
   uint8_t tmp = 0;
   uint8_t* ptmp[2] = {0,0};
   switch(cwtype)
   {
      case CW_RESET_WIZCHIP:
         wizchip_sw_reset();
         break;
      case CW_INIT_WIZCHIP:
         if(arg != 0) 
         {
            ptmp[0] = (uint8_t*)arg;
            ptmp[1] = ptmp[0] + _WIZCHIP_SOCK_NUM_;
         }
         return wizchip_init(ptmp[0], ptmp[1]);
      case CW_CLR_INTERRUPT:
         wizchip_clrinterrupt(*((intr_kind*)arg));
         break;
      case CW_GET_INTERRUPT:
        *((intr_kind*)arg) = wizchip_getinterrupt();
         break;
      case CW_SET_INTRMASK:
         wizchip_setinterruptmask(*((intr_kind*)arg));
         break;         
      case CW_GET_INTRMASK:
         *((intr_kind*)arg) = wizchip_getinterruptmask();
         break;
   #if _WIZCHIP_ > 5100
      case CW_SET_INTRTIME:
         setINTLEVEL(*(uint16_t*)arg);
         break;
      case CW_GET_INTRTIME:
         *(uint16_t*)arg = getINTLEVEL();
         break;
   #endif
      case CW_GET_ID:
         ((uint8_t*)arg)[0] = WIZCHIP.id[0];
         ((uint8_t*)arg)[1] = WIZCHIP.id[1];
         ((uint8_t*)arg)[2] = WIZCHIP.id[2];
         ((uint8_t*)arg)[3] = WIZCHIP.id[3];
         ((uint8_t*)arg)[4] = WIZCHIP.id[4];
         ((uint8_t*)arg)[5] = 0;
         break;
   #if _WIZCHIP_ ==  5500
      case CW_RESET_PHY:
         wizphy_reset();
         break;
      case CW_SET_PHYCONF:
         wizphy_setphyconf((wiz_PhyConf*)arg);
         break;
      case CW_GET_PHYCONF:
         wizphy_getphyconf((wiz_PhyConf*)arg);
         break;
      case CW_GET_PHYSTATUS:
         break;
      case CW_SET_PHYPOWMODE:
         return wizphy_setphypmode(*(uint8_t*)arg);
   #endif
      case CW_GET_PHYPOWMODE:
         tmp = wizphy_getphypmode();
         if((int8_t)tmp == -1) return -1;
         *(uint8_t*)arg = tmp;
         break;
      case CW_GET_PHYLINK:
         tmp = wizphy_getphylink();
         if((int8_t)tmp == -1) return -1;
         *(uint8_t*)arg = tmp;
         break;
      default:
         return -1;
   }
   return 0;
}