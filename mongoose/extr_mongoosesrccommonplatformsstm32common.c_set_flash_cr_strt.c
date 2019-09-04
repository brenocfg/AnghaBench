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
 int FLASH_F4_CR ; 
 int FLASH_F4_CR_STRT ; 
 int /*<<< orphan*/  stlink_read_debug32 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  stlink_write_debug32 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void set_flash_cr_strt(stlink_t *sl) {
  uint32_t val, cr_reg, cr_strt;

  cr_reg = FLASH_F4_CR;
  cr_strt = 1 << FLASH_F4_CR_STRT;

  stlink_read_debug32(sl, cr_reg, &val);
  val |= cr_strt;
  stlink_write_debug32(sl, cr_reg, val);
}