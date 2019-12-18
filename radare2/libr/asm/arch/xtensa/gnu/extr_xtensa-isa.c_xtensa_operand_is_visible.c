#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; } ;
typedef  TYPE_4__ xtensa_operand_internal ;
typedef  size_t xtensa_opcode ;
struct TYPE_14__ {TYPE_4__* operands; TYPE_6__* iclasses; TYPE_1__* opcodes; } ;
typedef  TYPE_5__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
struct TYPE_15__ {TYPE_3__* operands; } ;
typedef  TYPE_6__ xtensa_iclass_internal ;
struct TYPE_11__ {int operand_id; } ;
struct TYPE_12__ {char inout; TYPE_2__ u; } ;
struct TYPE_10__ {int iclass_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OPCODE (TYPE_5__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_OPERAND (TYPE_5__*,size_t,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int XTENSA_OPERAND_IS_INVISIBLE ; 
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 

int
xtensa_operand_is_visible (xtensa_isa isa, xtensa_opcode opc, int opnd)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_iclass_internal *iclass;
  int iclass_id, operand_id;
  xtensa_operand_internal *intop;

  CHECK_OPCODE (intisa, opc, XTENSA_UNDEFINED);
  iclass_id = intisa->opcodes[opc].iclass_id;
  iclass = &intisa->iclasses[iclass_id];
  CHECK_OPERAND (intisa, opc, iclass, opnd, XTENSA_UNDEFINED);

  /* Special case for "sout" operands.  */
  if (iclass->operands[opnd].inout == 's') {
	  return 0;
  }

  operand_id = iclass->operands[opnd].u.operand_id;
  intop = &intisa->operands[operand_id];

  if ((intop->flags & XTENSA_OPERAND_IS_INVISIBLE) == 0) {
	  return 1;
  }
  return 0;
}