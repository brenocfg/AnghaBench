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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  stm32_addr_t ;
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int /*<<< orphan*/  calculate_F7_sectornum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_flash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_flash_cr_strt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_flash_if (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_flash_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_flash_cr_snb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int stlink_erase_flash_page(stlink_t *sl, stm32_addr_t flashaddr) {
  /* wait for ongoing op to finish */
  wait_flash_busy(sl);

  /* unlock if locked */
  unlock_flash_if(sl);

  /* select the page to erase */
  // calculate the actual page from the address
  uint32_t sector = calculate_F7_sectornum(flashaddr);

  write_flash_cr_snb(sl, sector);

  /* start erase operation */
  set_flash_cr_strt(sl);

  /* wait for completion */
  wait_flash_busy(sl);

  /* relock the flash */
  // todo: fails to program if this is in
  lock_flash(sl);

  return 0;
}