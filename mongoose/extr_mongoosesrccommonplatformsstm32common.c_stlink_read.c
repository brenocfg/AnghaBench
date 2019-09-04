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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ stm32_addr_t ;
struct TYPE_4__ {size_t flash_size; int flash_pgsz; int /*<<< orphan*/  q_buf; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int /*<<< orphan*/  (* save_block_fn ) (void*,int /*<<< orphan*/ ,size_t) ;

/* Variables and functions */
 int /*<<< orphan*/  stlink_read_mem32 (TYPE_1__*,scalar_t__,size_t) ; 

__attribute__((used)) static int stlink_read(stlink_t *sl, stm32_addr_t addr, size_t size,
                       save_block_fn fn, void *fn_arg) {
  int error = -1;

  if (size < 1) size = sl->flash_size;

  if (size > sl->flash_size) size = sl->flash_size;

  size_t cmp_size = (sl->flash_pgsz > 0x1800) ? 0x1800 : sl->flash_pgsz;
  for (size_t off = 0; off < size; off += cmp_size) {
    size_t aligned_size;

    /* adjust last page size */
    if ((off + cmp_size) > size) cmp_size = size - off;

    aligned_size = cmp_size;
    if (aligned_size & (4 - 1)) aligned_size = (cmp_size + 4) & ~(4 - 1);

    stlink_read_mem32(sl, addr + (uint32_t) off, aligned_size);

    if (!fn(fn_arg, sl->q_buf, aligned_size)) {
      goto on_error;
    }
  }

  /* success */
  error = 0;

on_error:
  return error;
}