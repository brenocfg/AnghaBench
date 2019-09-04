#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  target; int /*<<< orphan*/  (* print_address_func ) (int /*<<< orphan*/ ,struct disassemble_info*) ;} ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ aarch64_opnd_info ;
struct TYPE_8__ {scalar_t__* operands; } ;
typedef  TYPE_2__ aarch64_opcode ;

/* Variables and functions */
 int AARCH64_MAX_OPND_NUM ; 
 scalar_t__ AARCH64_OPND_NIL ; 
 int /*<<< orphan*/  aarch64_print_operand (char*,int,int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_1__ const*,int,int*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  no_notes ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
print_operands (bfd_vma pc, const aarch64_opcode *opcode,
		const aarch64_opnd_info *opnds, struct disassemble_info *info)
{
  int i, pcrel_p, num_printed;
  char *notes = NULL;
  for (i = 0, num_printed = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    {
      char str[128];
      /* We regard the opcode operand info more, however we also look into
	 the inst->operands to support the disassembling of the optional
	 operand.
	 The two operand code should be the same in all cases, apart from
	 when the operand can be optional.  */
      if (opcode->operands[i] == AARCH64_OPND_NIL
	  || opnds[i].type == AARCH64_OPND_NIL)
	break;

      /* Generate the operand string in STR.  */
      aarch64_print_operand (str, sizeof (str), pc, opcode, opnds, i, &pcrel_p,
			     &info->target, &notes);

      /* Print the delimiter (taking account of omitted operand(s)).  */
      if (str[0] != '\0')
	(*info->fprintf_func) (info->stream, "%s",
			       num_printed++ == 0 ? " " : ", ");

      /* Print the operand.  */
      if (pcrel_p)
	(*info->print_address_func) (info->target, info);
      else
	(*info->fprintf_func) (info->stream, "%s", str);
    }

    if (notes && !no_notes)
      (*info->fprintf_func) (info->stream, " ; note: %s", notes);
}