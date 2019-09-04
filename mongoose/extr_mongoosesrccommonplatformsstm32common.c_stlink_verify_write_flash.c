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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ stm32_addr_t ;
struct TYPE_4__ {int flash_pgsz; int /*<<< orphan*/  q_buf; } ;
typedef  TYPE_1__ stlink_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stlink_read_mem32 (TYPE_1__*,scalar_t__,size_t) ; 

int stlink_verify_write_flash(stlink_t *sl, stm32_addr_t address, uint8_t *data,
                              unsigned length) {
  size_t off;
  size_t cmp_size = (sl->flash_pgsz > 0x1800) ? 0x1800 : sl->flash_pgsz;
  printf("Verifying flash...\n");
  for (off = 0; off < length; off += cmp_size) {
    size_t aligned_size;

    /* adjust last page size */
    if ((off + cmp_size) > length) cmp_size = length - off;

    aligned_size = cmp_size;
    if (aligned_size & (4 - 1)) aligned_size = (cmp_size + 4) & ~(4 - 1);

    stlink_read_mem32(sl, address + (uint32_t) off, aligned_size);

    if (memcmp(sl->q_buf, data + off, cmp_size)) {
      printf("Verification of flash failed at offset: %u\n",
             (unsigned int) off);
      return -1;
    }
  }
  return 0;
}