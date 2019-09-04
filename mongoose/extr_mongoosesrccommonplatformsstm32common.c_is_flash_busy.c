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
 int FLASH_F4_SR_BSY ; 
 int read_flash_sr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int is_flash_busy(stlink_t *sl) {
  uint32_t sr_busy_shift;
  sr_busy_shift = FLASH_F4_SR_BSY;
  return read_flash_sr(sl) & (1 << sr_busy_shift);
}