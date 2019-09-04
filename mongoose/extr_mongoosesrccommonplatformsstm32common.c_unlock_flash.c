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
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_F4_KEYR ; 
 int /*<<< orphan*/  FLASH_KEY1 ; 
 int /*<<< orphan*/  FLASH_KEY2 ; 
 int /*<<< orphan*/  stlink_write_debug32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlock_flash(stlink_t *sl) {
  uint32_t key_reg = FLASH_F4_KEYR;
  stlink_write_debug32(sl, key_reg, FLASH_KEY1);
  stlink_write_debug32(sl, key_reg, FLASH_KEY2);
}