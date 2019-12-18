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
typedef  int* xtensa_insnbuf ;

/* Variables and functions */

__attribute__((used)) static void
Slot_xt_format2_Format_xt_flix64_slot3_28_set (xtensa_insnbuf insn,
					      const xtensa_insnbuf slotbuf)
{
  insn[0] = (insn[0] & ~0xf0000000) | ((slotbuf[0] & 0xf) << 28);
  insn[1] = (insn[1] & ~0xfffffff) | ((slotbuf[0] & 0xfffffff0) >> 4);
  insn[1] = (insn[1] & ~0x70000000) | ((slotbuf[1] & 0x7) << 28);
}