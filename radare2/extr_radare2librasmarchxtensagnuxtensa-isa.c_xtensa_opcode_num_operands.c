#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t xtensa_opcode ;
struct TYPE_7__ {TYPE_2__* iclasses; TYPE_1__* opcodes; } ;
typedef  TYPE_3__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
struct TYPE_6__ {int num_operands; } ;
struct TYPE_5__ {int iclass_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OPCODE (TYPE_3__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 

int
xtensa_opcode_num_operands (xtensa_isa isa, xtensa_opcode opc)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  int iclass_id;

  CHECK_OPCODE (intisa, opc, XTENSA_UNDEFINED);
  iclass_id = intisa->opcodes[opc].iclass_id;
  return intisa->iclasses[iclass_id].num_operands;
}