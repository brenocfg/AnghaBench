#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct stlink_reg {scalar_t__* r; } ;
typedef  int /*<<< orphan*/  stm32_addr_t ;
typedef  int /*<<< orphan*/  stlink_t ;
struct TYPE_4__ {int /*<<< orphan*/  loader_addr; int /*<<< orphan*/  buf_addr; } ;
typedef  TYPE_1__ flash_loader_t ;

/* Variables and functions */
 int WAIT_ROUNDS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stlink_is_core_halted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_read_reg (int /*<<< orphan*/ *,int,struct stlink_reg*) ; 
 int /*<<< orphan*/  stlink_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write_buffer_to_sram (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 

int stlink_flash_loader_run(stlink_t *sl, flash_loader_t *fl,
                            stm32_addr_t target, const uint8_t *buf,
                            size_t size) {
  struct stlink_reg rr;
  int i = 0;
  size_t count = 0;

  // FIXME This can never return -1
  if (write_buffer_to_sram(sl, fl, buf, size) == -1) {
    // IMPOSSIBLE!
    printf("write_buffer_to_sram() == -1\n");
    return -1;
  }

  count = size / sizeof(uint32_t);
  if (size % sizeof(uint32_t)) ++count;

  /* setup core */
  stlink_write_reg(sl, fl->buf_addr, 0);     /* source */
  stlink_write_reg(sl, target, 1);           /* target */
  stlink_write_reg(sl, (uint32_t) count, 2); /* count */
  stlink_write_reg(
      sl, 0,
      3); /* flash bank 0 (input), only used on F0, but armless fopr others */
  stlink_write_reg(sl, fl->loader_addr, 15); /* pc register */

  /* run loader */
  stlink_run(sl);

  /* wait until done (reaches breakpoint) */
  for (i = 0; i < WAIT_ROUNDS; i++) {
    usleep(10);
    if (stlink_is_core_halted(sl)) break;
  }

  if (i >= WAIT_ROUNDS) {
    printf("flash loader run error\n");
    return -1;
  }

  /* check written byte count */
  stlink_read_reg(sl, 2, &rr);
  if (rr.r[2] != 0) {
    printf("write error, count == %u\n", rr.r[2]);
    return -1;
  }

  return 0;
}