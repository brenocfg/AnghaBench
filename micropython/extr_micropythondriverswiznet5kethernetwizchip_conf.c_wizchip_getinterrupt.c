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
typedef  int /*<<< orphan*/  intr_kind ;

/* Variables and functions */
 int getIR () ; 
 int getSIR () ; 

intr_kind wizchip_getinterrupt(void)
{
   uint8_t ir  = 0;
   uint8_t sir = 0;
   uint16_t ret = 0;
#if _WIZCHIP_ == 5100
   ir = getIR();
   sir = ir 0x0F;
#else
   ir  = getIR();
   sir = getSIR();
#endif         

#if _WIZCHIP_ < 5500
   ir &= ~(1<<4); // IK_WOL
#endif
#if _WIZCHIP_ == 5200
   ir &= ~(1 << 6);
#endif
  ret = sir;
  ret = (ret << 8) + ir;
  return (intr_kind)ret;
}