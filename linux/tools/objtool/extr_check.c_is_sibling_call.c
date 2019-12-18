#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct instruction {scalar_t__ type; int /*<<< orphan*/  call_dest; int /*<<< orphan*/  alts; } ;

/* Variables and functions */
 scalar_t__ INSN_JUMP_CONDITIONAL ; 
 scalar_t__ INSN_JUMP_DYNAMIC ; 
 scalar_t__ INSN_JUMP_UNCONDITIONAL ; 
 int list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_sibling_call(struct instruction *insn)
{
	/* An indirect jump is either a sibling call or a jump to a table. */
	if (insn->type == INSN_JUMP_DYNAMIC)
		return list_empty(&insn->alts);

	if (insn->type != INSN_JUMP_CONDITIONAL &&
	    insn->type != INSN_JUMP_UNCONDITIONAL)
		return false;

	/* add_jump_destinations() sets insn->call_dest for sibling calls. */
	return !!insn->call_dest;
}