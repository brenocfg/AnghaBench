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
struct TYPE_8__ {TYPE_1__* operands; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ aarch64_inst ;
struct TYPE_9__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ aarch64_field ;
struct TYPE_7__ {int /*<<< orphan*/  qualifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPND_QLF_S_S ; 
 int /*<<< orphan*/  FLD_size ; 
 int /*<<< orphan*/  extract_field_2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sub_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 

__attribute__((used)) static int
decode_asisd_fcvtxn (aarch64_inst *inst)
{
  aarch64_field field = {0, 0};
  gen_sub_field (FLD_size, 0, 1, &field);
  if (!extract_field_2 (&field, inst->value, 0))
    return 0;
  inst->operands[0].qualifier = AARCH64_OPND_QLF_S_S;
  return 1;
}