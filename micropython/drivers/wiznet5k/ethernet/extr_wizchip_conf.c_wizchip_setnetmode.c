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
typedef  int netmode_type ;
typedef  int int8_t ;

/* Variables and functions */
 int NM_FORCEARP ; 
 int NM_PINGBLOCK ; 
 int NM_PPPOE ; 
 int NM_WAKEONLAN ; 
 int /*<<< orphan*/  getMR () ; 
 int /*<<< orphan*/  setMR (int /*<<< orphan*/ ) ; 

int8_t wizchip_setnetmode(netmode_type netmode)
{
   uint8_t tmp = 0;
#if _WIZCHIP_ != 5500   
   if(netmode & ~(NM_WAKEONLAN | NM_PPPOE | NM_PINGBLOCK)) return -1;
#else
   if(netmode & ~(NM_WAKEONLAN | NM_PPPOE | NM_PINGBLOCK | NM_FORCEARP)) return -1;
#endif      
   tmp = getMR();
   tmp |= (uint8_t)netmode;
   setMR(tmp);
   return 0;
}