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
struct TYPE_3__ {int /*<<< orphan*/ ** qualifiers_list; int /*<<< orphan*/ * operands; } ;
typedef  TYPE_1__ aarch64_opcode ;

/* Variables and functions */
 scalar_t__ AARCH64_OPND_CLASS_SISD_REG ; 
 scalar_t__ aarch64_get_operand_class (int /*<<< orphan*/ ) ; 
 int aarch64_get_qualifier_esize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
select_operand_for_scalar_size_field_coding (const aarch64_opcode *opcode)
{
  int src_size = 0, dst_size = 0;
  if (aarch64_get_operand_class (opcode->operands[0])
      == AARCH64_OPND_CLASS_SISD_REG)
    dst_size = aarch64_get_qualifier_esize (opcode->qualifiers_list[0][0]);
  if (aarch64_get_operand_class (opcode->operands[1])
      == AARCH64_OPND_CLASS_SISD_REG)
    src_size = aarch64_get_qualifier_esize (opcode->qualifiers_list[0][1]);
  if (src_size == dst_size && src_size == 0)
    { assert (0); abort (); }
  /* When the result is not a sisd register or it is a long operantion.  */
  if (dst_size == 0 || dst_size == src_size << 1)
    return 1;
  else
    return 0;
}