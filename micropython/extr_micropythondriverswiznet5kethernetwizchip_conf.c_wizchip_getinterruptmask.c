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
 int getIMR () ; 
 int getSIMR () ; 

intr_kind wizchip_getinterruptmask(void)
{
   uint8_t imr  = 0;
   uint8_t simr = 0;
   uint16_t ret = 0;
#if _WIZCHIP_ == 5100
   imr  = getIMR();
   simr = imr 0x0F;
#else
   imr  = getIMR();
   simr = getSIMR();
#endif         

#if _WIZCHIP_ < 5500
   imr &= ~(1<<4); // IK_WOL
#endif
#if _WIZCHIP_ == 5200
   imr &= ~(1 << 6);  // IK_DEST_UNREACH
#endif
  ret = simr;
  ret = (ret << 8) + imr;
  return (intr_kind)ret;
}