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
typedef  int uint32_t ;

/* Variables and functions */
 int STM32_FLASH_BASE ; 

uint32_t calculate_F7_sectornum(uint32_t flashaddr) {
  flashaddr &= ~STM32_FLASH_BASE;  // Page now holding the actual flash address
  if (flashaddr < 0x20000)
    return (flashaddr / 0x8000);
  else if (flashaddr < 0x40000)
    return (4);
  else
    return (flashaddr / 0x40000) + 4;
}