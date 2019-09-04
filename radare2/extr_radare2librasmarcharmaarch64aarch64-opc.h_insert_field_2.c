#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int aarch64_insn ;
struct TYPE_3__ {int width; int lsb; } ;
typedef  TYPE_1__ aarch64_field ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int gen_mask (int) ; 

__attribute__((used)) static inline void
insert_field_2 (const aarch64_field *field, aarch64_insn *code,
		aarch64_insn value, aarch64_insn mask)
{
  assert (field->width < 32 && field->width >= 1 && field->lsb >= 0
	  && field->lsb + field->width <= 32);
  value &= gen_mask (field->width);
  value <<= field->lsb;
  /* In some opcodes, field can be part of the base opcode, e.g. the size
     field in FADD.  The following helps avoid corrupt the base opcode.  */
  value &= ~mask;
  *code |= value;
}