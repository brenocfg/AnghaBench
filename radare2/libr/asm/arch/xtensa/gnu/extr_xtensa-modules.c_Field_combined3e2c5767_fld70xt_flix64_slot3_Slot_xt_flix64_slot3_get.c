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

__attribute__((used)) static unsigned
Field_combined3e2c5767_fld70xt_flix64_slot3_Slot_xt_flix64_slot3_get (const xtensa_insnbuf insn)
{
  unsigned tie_t = 0;
  tie_t = (tie_t << 3) | ((insn[1] << 29) >> 29);
  tie_t = (tie_t << 1) | ((insn[0] << 5) >> 31);
  tie_t = (tie_t << 4) | ((insn[0] << 28) >> 28);
  return tie_t;
}