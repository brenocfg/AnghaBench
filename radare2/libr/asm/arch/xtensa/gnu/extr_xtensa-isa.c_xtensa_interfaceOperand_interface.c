#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t xtensa_opcode ;
struct TYPE_8__ {TYPE_3__* iclasses; TYPE_1__* opcodes; } ;
typedef  TYPE_2__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_interface ;
struct TYPE_9__ {int /*<<< orphan*/ * interfaceOperands; } ;
typedef  TYPE_3__ xtensa_iclass_internal ;
struct TYPE_7__ {int iclass_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_INTERFACE_OPERAND (TYPE_2__*,size_t,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_OPCODE (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 

xtensa_interface
xtensa_interfaceOperand_interface (xtensa_isa isa, xtensa_opcode opc,
				   int ifOp)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_iclass_internal *iclass;
  int iclass_id;

  CHECK_OPCODE (intisa, opc, XTENSA_UNDEFINED);
  iclass_id = intisa->opcodes[opc].iclass_id;
  iclass = &intisa->iclasses[iclass_id];
  CHECK_INTERFACE_OPERAND (intisa, opc, iclass, ifOp, XTENSA_UNDEFINED);
  return iclass->interfaceOperands[ifOp];
}