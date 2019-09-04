#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum aarch64_opnd_qualifier { ____Placeholder_aarch64_opnd_qualifier } aarch64_opnd_qualifier ;
struct TYPE_7__ {TYPE_1__* operands; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ aarch64_inst ;
typedef  int aarch64_insn ;
struct TYPE_8__ {int member_0; int member_1; } ;
typedef  TYPE_3__ aarch64_field ;
struct TYPE_6__ {int qualifier; } ;

/* Variables and functions */
 int AARCH64_OPND_QLF_S_D ; 
 int AARCH64_OPND_QLF_S_H ; 
 int AARCH64_OPND_QLF_S_S ; 
 int extract_field_2 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decode_fcvt (aarch64_inst *inst)
{
  enum aarch64_opnd_qualifier qualifier;
  aarch64_insn value;
  const aarch64_field field = {15, 2};

  /* opc dstsize */
  value = extract_field_2 (&field, inst->value, 0);
  switch (value)
    {
    case 0: qualifier = AARCH64_OPND_QLF_S_S; break;
    case 1: qualifier = AARCH64_OPND_QLF_S_D; break;
    case 3: qualifier = AARCH64_OPND_QLF_S_H; break;
    default: return 0;
    }
  inst->operands[0].qualifier = qualifier;

  return 1;
}