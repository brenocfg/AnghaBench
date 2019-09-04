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
 int /*<<< orphan*/  FLASH_F4_CR ; 
 int FLASH_F4_CR_SER ; 
 int FLASH_F4_CR_SNB ; 
 int FLASH_F4_CR_SNB_MASK ; 
 int read_flash_cr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_write_debug32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void write_flash_cr_snb(stlink_t *sl, uint32_t n) {
  uint32_t x = read_flash_cr(sl);
  x &= ~FLASH_F4_CR_SNB_MASK;
  x |= (n << FLASH_F4_CR_SNB);
  x |= (1 << FLASH_F4_CR_SER);
  stlink_write_debug32(sl, FLASH_F4_CR, x);
}