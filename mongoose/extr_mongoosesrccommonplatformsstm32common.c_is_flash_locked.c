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
 int FLASH_F4_CR_LOCK ; 
 int read_flash_cr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int is_flash_locked(stlink_t *sl) {
  /* return non zero for true */
  uint32_t cr_lock_shift = FLASH_F4_CR_LOCK, cr = read_flash_cr(sl);
  return cr & (1 << cr_lock_shift);
}