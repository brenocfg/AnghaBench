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
 int /*<<< orphan*/  setIR (int) ; 
 int /*<<< orphan*/  setSIR (int) ; 

void wizchip_clrinterrupt(intr_kind intr)
{
   uint8_t ir  = (uint8_t)intr;
   uint8_t sir = (uint8_t)((uint16_t)intr >> 8);
#if _WIZCHIP_ < 5500
   ir |= (1<<4); // IK_WOL
#endif
#if _WIZCHIP_ == 5200
   ir |= (1 << 6);
#endif
   
#if _WIZCHIP_ < 5200
   sir &= 0x0F;
#endif

#if _WIZCHIP_ == 5100
   ir |= sir;
   setIR(ir);
#else
   setIR(ir);
   setSIR(sir);
#endif   
}