#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  q_buf; } ;
typedef  TYPE_1__ stlink_t ;
struct TYPE_8__ {scalar_t__ buf_addr; } ;
typedef  TYPE_2__ flash_loader_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  stlink_write_mem32 (TYPE_1__*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  stlink_write_mem8 (TYPE_1__*,scalar_t__,size_t) ; 

int write_buffer_to_sram(stlink_t *sl, flash_loader_t *fl, const uint8_t *buf,
                         size_t size) {
  /* write the buffer right after the loader */
  size_t chunk = size & ~0x3;
  size_t rem = size & 0x3;
  if (chunk) {
    memcpy(sl->q_buf, buf, chunk);
    stlink_write_mem32(sl, fl->buf_addr, chunk);
  }
  if (rem) {
    memcpy(sl->q_buf, buf + chunk, rem);
    stlink_write_mem8(sl, (fl->buf_addr) + (uint32_t) chunk, rem);
  }
  return 0;
}