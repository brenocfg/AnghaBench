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
typedef  int /*<<< orphan*/  xtensa_regfile ;
struct TYPE_3__ {int /*<<< orphan*/  regfile; } ;
typedef  TYPE_1__ xtensa_operand_internal ;
typedef  int /*<<< orphan*/  xtensa_opcode ;
typedef  int /*<<< orphan*/  xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;

/* Variables and functions */
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 
 TYPE_1__* get_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

xtensa_regfile
xtensa_operand_regfile (xtensa_isa isa, xtensa_opcode opc, int opnd)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_operand_internal *intop;

  intop = get_operand (intisa, opc, opnd);
  if (!intop) {
	  return XTENSA_UNDEFINED;
  }

  return intop->regfile;
}