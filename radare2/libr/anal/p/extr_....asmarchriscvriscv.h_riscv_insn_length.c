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
typedef  int insn_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int riscv_insn_length (insn_t insn)
{
  if ((insn & 0x3) != 0x3) /* RVC.  */
    return 2;
  if ((insn & 0x1f) != 0x1f) /* Base ISA and extensions in 32-bit space.  */
    return 4;
  if ((insn & 0x3f) == 0x1f) /* 48-bit extensions.  */
    return 6;
  if ((insn & 0x7f) == 0x3f) /* 64-bit extensions.  */
    return 8;
  /* Longer instructions not supported at the moment.  */
  return 2;
}