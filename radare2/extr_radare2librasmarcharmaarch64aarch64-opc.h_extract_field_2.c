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
struct TYPE_3__ {int lsb; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ aarch64_field ;

/* Variables and functions */
 int gen_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline aarch64_insn
extract_field_2 (const aarch64_field *field, aarch64_insn code,
		 aarch64_insn mask)
{
  aarch64_insn value;
  /* Clear any bit that is a part of the base opcode.  */
  code &= ~mask;
  value = (code >> field->lsb) & gen_mask (field->width);
  return value;
}