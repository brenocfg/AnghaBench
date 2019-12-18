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
struct disassemble_info {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*,char*,char*,scalar_t__) ;} ;
struct TYPE_8__ {TYPE_2__* cond; TYPE_1__* opcode; } ;
typedef  TYPE_3__ aarch64_inst ;
struct TYPE_7__ {scalar_t__* names; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int F_COND ; 
 int /*<<< orphan*/  remove_dot_suffix (char*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*,char*,scalar_t__) ; 

__attribute__((used)) static void
print_comment (const aarch64_inst *inst, struct disassemble_info *info)
{
return;
  if (inst->opcode->flags & F_COND)
    {
      char name[8];
      unsigned int i, num_conds;

      remove_dot_suffix (name, inst);
      num_conds = ARRAY_SIZE (inst->cond->names);
      for (i = 1; i < num_conds && inst->cond->names[i]; ++i)
	(*info->fprintf_func) (info->stream, "%s %s.%s",
			       i == 1 ? "  //" : ",",
			       name, inst->cond->names[i]);
    }
}