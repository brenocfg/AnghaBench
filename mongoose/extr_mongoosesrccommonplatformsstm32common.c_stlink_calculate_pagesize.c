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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ chip_id; int flash_pgsz; } ;
typedef  TYPE_1__ stlink_t ;

/* Variables and functions */
 scalar_t__ STLINK_CHIPID_STM32_F7 ; 
 int calculate_F7_sectornum (int) ; 

uint32_t stlink_calculate_pagesize(stlink_t *sl, uint32_t flashaddr) {
  if (sl->chip_id == STLINK_CHIPID_STM32_F7) {
    uint32_t sector = calculate_F7_sectornum(flashaddr);
    if (sector < 4)
      sl->flash_pgsz = 0x8000;
    else if (sector < 5)
      sl->flash_pgsz = 0x20000;
    else
      sl->flash_pgsz = 0x40000;
  }
  return (uint32_t) sl->flash_pgsz;
}