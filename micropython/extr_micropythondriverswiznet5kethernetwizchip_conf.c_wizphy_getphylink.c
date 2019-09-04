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
typedef  int int8_t ;

/* Variables and functions */

int8_t wizphy_getphylink(void)
{
   int8_t tmp;
#if   _WIZCHIP_ == 5200
   if(getPHYSTATUS() & PHYSTATUS_LINK)
      tmp = PHY_LINK_ON;
   else
      tmp = PHY_LINK_OFF;
#elif _WIZCHIP_ == 5500
   if(getPHYCFGR() & PHYCFGR_LNK_ON)
      tmp = PHY_LINK_ON;
   else
      tmp = PHY_LINK_OFF;
#else
   tmp = -1;
#endif
   return tmp;
}