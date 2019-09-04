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
Field_mn_Slot_inst_get (const xtensa_insnbuf insn)
{
  unsigned tie_t = 0;
  tie_t = (tie_t << 2) | ((insn[0] << 24) >> 30);
  tie_t = (tie_t << 2) | ((insn[0] << 26) >> 30);
  return tie_t;
}