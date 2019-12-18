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
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static void
Field_combined3e2c5767_fld7_Slot_xt_flix64_slot0_set (xtensa_insnbuf insn, uint32 val)
{
  uint32 tie_t;
  tie_t = (val << 29) >> 29;
  insn[0] = (insn[0] & ~0xe000) | (tie_t << 13);
}