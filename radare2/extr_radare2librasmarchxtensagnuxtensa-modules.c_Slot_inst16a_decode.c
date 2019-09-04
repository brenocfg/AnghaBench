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
typedef  int /*<<< orphan*/  xtensa_insnbuf ;

/* Variables and functions */
 int Field_op0_Slot_inst16a_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_inst16a_decode (const xtensa_insnbuf insn)
{
  switch (Field_op0_Slot_inst16a_get (insn))
    {
    case 8:
      return 31; /* l32i.n */
    case 9:
      return 36; /* s32i.n */
    case 10:
      return 26; /* add.n */
    case 11:
      return 27; /* addi.n */
    }
  return 0;
}