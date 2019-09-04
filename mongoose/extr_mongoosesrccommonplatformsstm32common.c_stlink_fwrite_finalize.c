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
typedef  scalar_t__ stm32_addr_t ;
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int /*<<< orphan*/  stlink_read_debug32 (int /*<<< orphan*/ *,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  stlink_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_write_reg (int /*<<< orphan*/ *,unsigned int,int) ; 

void stlink_fwrite_finalize(stlink_t *sl, stm32_addr_t addr) {
  unsigned int val;
  /* set stack*/
  stlink_read_debug32(sl, addr, &val);
  stlink_write_reg(sl, val, 13);
  /* Set PC to the reset routine*/
  stlink_read_debug32(sl, addr + 4, &val);
  stlink_write_reg(sl, val, 15);
  stlink_run(sl);
}