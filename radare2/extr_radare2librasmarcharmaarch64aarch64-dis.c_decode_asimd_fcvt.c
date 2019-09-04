#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_opnd_qualifier { ____Placeholder_aarch64_opnd_qualifier } aarch64_opnd_qualifier ;
struct TYPE_10__ {TYPE_2__* operands; TYPE_1__* opcode; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ aarch64_inst ;
typedef  scalar_t__ aarch64_insn ;
struct TYPE_11__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ aarch64_field ;
struct TYPE_9__ {int qualifier; } ;
struct TYPE_8__ {int op; } ;

/* Variables and functions */
 int AARCH64_OPND_QLF_V_2D ; 
 int AARCH64_OPND_QLF_V_4S ; 
 int /*<<< orphan*/  FLD_size ; 
#define  OP_FCVTL 131 
#define  OP_FCVTL2 130 
#define  OP_FCVTN 129 
#define  OP_FCVTN2 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ extract_field_2 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sub_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*) ; 

__attribute__((used)) static int
decode_asimd_fcvt (aarch64_inst *inst)
{
  aarch64_field field = {0, 0};
  aarch64_insn value;
  enum aarch64_opnd_qualifier qualifier;

  gen_sub_field (FLD_size, 0, 1, &field);
  value = extract_field_2 (&field, inst->value, 0);
  qualifier = value == 0 ? AARCH64_OPND_QLF_V_4S
    : AARCH64_OPND_QLF_V_2D;
  switch (inst->opcode->op)
    {
    case OP_FCVTN:
    case OP_FCVTN2:
      /* FCVTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
      inst->operands[1].qualifier = qualifier;
      break;
    case OP_FCVTL:
    case OP_FCVTL2:
      /* FCVTL<Q> <Vd>.<Ta>, <Vn>.<Tb>.  */
      inst->operands[0].qualifier = qualifier;
      break;
    default:
      assert (0);
      return 0;
    }

  return 1;
}