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
 int /*<<< orphan*/  FLASH_F4_CR ; 
 int /*<<< orphan*/  stlink_read_debug32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t read_flash_cr(stlink_t *sl) {
  uint32_t res;
  stlink_read_debug32(sl, FLASH_F4_CR, &res);
  return res;
}