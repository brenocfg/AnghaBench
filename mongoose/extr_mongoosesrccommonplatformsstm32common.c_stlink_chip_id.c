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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int stlink_read_debug32 (int /*<<< orphan*/ *,int,scalar_t__*) ; 

int stlink_chip_id(stlink_t *sl, uint32_t *chip_id) {
  int ret;

  ret = stlink_read_debug32(sl, 0xE0042000, chip_id);
  if (ret == -1) return ret;

  if (*chip_id == 0)
    ret = stlink_read_debug32(
        sl, 0x40015800,
        chip_id);  // Try Corex M0 DBGMCU_IDCODE register address

  return ret;
}