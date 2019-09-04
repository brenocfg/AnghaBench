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
typedef  int uint16_t ;
typedef  scalar_t__ intr_kind ;

/* Variables and functions */
 int /*<<< orphan*/  setIMR (int) ; 
 int /*<<< orphan*/  setSIMR (int) ; 

void wizchip_setinterruptmask(intr_kind intr)
{
   uint8_t imr  = (uint8_t)intr;
   uint8_t simr = (uint8_t)((uint16_t)intr >> 8);
#if _WIZCHIP_ < 5500
   imr &= ~(1<<4); // IK_WOL
#endif
#if _WIZCHIP_ == 5200
   imr &= ~(1 << 6);
#endif
   
#if _WIZCHIP_ < 5200
   simr &= 0x0F;
#endif

#if _WIZCHIP_ == 5100
   imr |= simr;
   setIMR(imr);
#else
   setIMR(imr);
   setSIMR(simr);
#endif   
}