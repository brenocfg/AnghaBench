#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ (* undo_reloc ) (int*,int) ;} ;
typedef  TYPE_1__ xtensa_operand_internal ;
typedef  int /*<<< orphan*/  xtensa_opcode ;
typedef  int /*<<< orphan*/  xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int uint32 ;

/* Variables and functions */
 int XTENSA_OPERAND_IS_PCRELATIVE ; 
 TYPE_1__* get_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int*,int) ; 
 int /*<<< orphan*/  xtensa_isa_bad_value ; 
 int /*<<< orphan*/  xtensa_isa_internal_error ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

int
xtensa_operand_undo_reloc (xtensa_isa isa, xtensa_opcode opc, int opnd,
			   uint32 *valp, uint32 pc)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_operand_internal *intop;

  intop = get_operand (intisa, opc, opnd);
  if (!intop) {
	  return -1;
  }

  if ((intop->flags & XTENSA_OPERAND_IS_PCRELATIVE) == 0) {
	  return 0;
  }

  if (!intop->undo_reloc)
    {
      xtisa_errno = xtensa_isa_internal_error;
      strcpy (xtisa_error_msg, "operand missing undo_reloc function");
      return -1;
    }

  if ((*intop->undo_reloc) (valp, pc))
    {
      xtisa_errno = xtensa_isa_bad_value;
      sprintf (xtisa_error_msg,
	       "undo_reloc failed for value 0x%08x at PC 0x%08x", *valp, pc);
      return -1;
    }

  return 0;
}