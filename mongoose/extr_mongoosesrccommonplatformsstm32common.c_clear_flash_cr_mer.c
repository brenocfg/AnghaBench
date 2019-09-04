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
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int FLASH_CR_MER ; 
 int FLASH_F4_CR ; 
 int /*<<< orphan*/  stlink_read_debug32 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  stlink_write_debug32 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void __attribute__((unused)) clear_flash_cr_mer(stlink_t *sl) {
  uint32_t val, cr_reg, cr_mer;

  cr_reg = FLASH_F4_CR;
  cr_mer = 1 << FLASH_CR_MER;

  stlink_read_debug32(sl, cr_reg, &val);
  val &= ~cr_mer;
  stlink_write_debug32(sl, cr_reg, val);
}