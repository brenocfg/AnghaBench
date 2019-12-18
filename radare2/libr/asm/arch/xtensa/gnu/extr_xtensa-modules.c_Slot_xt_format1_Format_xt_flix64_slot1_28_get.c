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
Slot_xt_format1_Format_xt_flix64_slot1_28_get (const xtensa_insnbuf insn,
					      xtensa_insnbuf slotbuf)
{
  slotbuf[1] = 0;
  slotbuf[0] = ((insn[0] & 0xf0000000) >> 28);
  slotbuf[0] = (slotbuf[0] & ~0xffff0) | ((insn[1] & 0xffff) << 4);
}