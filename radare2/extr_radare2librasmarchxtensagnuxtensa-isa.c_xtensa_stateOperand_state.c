#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xtensa_state ;
typedef  size_t xtensa_opcode ;
struct TYPE_12__ {TYPE_5__* iclasses; TYPE_3__* opcodes; } ;
typedef  TYPE_4__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
struct TYPE_13__ {TYPE_2__* stateOperands; } ;
typedef  TYPE_5__ xtensa_iclass_internal ;
struct TYPE_11__ {int iclass_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_10__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OPCODE (TYPE_4__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_STATE_OPERAND (TYPE_4__*,size_t,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 

xtensa_state
xtensa_stateOperand_state (xtensa_isa isa, xtensa_opcode opc, int stOp)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_iclass_internal *iclass;
  int iclass_id;

  CHECK_OPCODE (intisa, opc, XTENSA_UNDEFINED);
  iclass_id = intisa->opcodes[opc].iclass_id;
  iclass = &intisa->iclasses[iclass_id];
  CHECK_STATE_OPERAND (intisa, opc, iclass, stOp, XTENSA_UNDEFINED);
  return iclass->stateOperands[stOp].u.state;
}