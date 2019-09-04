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
struct ud {char* asm_buf_int; char* asm_buf; size_t asm_buf_size; } ;

/* Variables and functions */

void
ud_set_asm_buffer(struct ud *u, char *buf, size_t size)
{
  if (buf == NULL) {
    ud_set_asm_buffer(u, u->asm_buf_int, sizeof(u->asm_buf_int));
  } else {
    u->asm_buf = buf;
    u->asm_buf_size = size;
  }
}