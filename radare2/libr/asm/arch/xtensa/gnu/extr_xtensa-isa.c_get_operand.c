#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xtensa_operand_internal ;
typedef  size_t xtensa_opcode ;
struct TYPE_13__ {int /*<<< orphan*/ * operands; TYPE_5__* iclasses; TYPE_3__* opcodes; } ;
typedef  TYPE_4__ xtensa_isa_internal ;
struct TYPE_14__ {TYPE_2__* operands; } ;
typedef  TYPE_5__ xtensa_iclass_internal ;
struct TYPE_12__ {int iclass_id; } ;
struct TYPE_10__ {int operand_id; } ;
struct TYPE_11__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OPCODE (TYPE_4__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_OPERAND (TYPE_4__*,size_t,TYPE_5__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xtensa_operand_internal *
get_operand (xtensa_isa_internal *intisa, xtensa_opcode opc, int opnd)
{
  xtensa_iclass_internal *iclass;
  int iclass_id, operand_id;

  CHECK_OPCODE (intisa, opc, NULL);
  iclass_id = intisa->opcodes[opc].iclass_id;
  iclass = &intisa->iclasses[iclass_id];
  CHECK_OPERAND (intisa, opc, iclass, opnd, NULL);
  operand_id = iclass->operands[opnd].u.operand_id;
  return &intisa->operands[operand_id];
}