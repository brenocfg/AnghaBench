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
typedef  int /*<<< orphan*/  stm32_addr_t ;
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 scalar_t__ stlink_is_core_halted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

void stlink_run_at(stlink_t *sl, stm32_addr_t addr) {
  stlink_write_reg(sl, addr, 15); /* pc register */

  stlink_run(sl);

  while (stlink_is_core_halted(sl)) usleep(3000000);
}