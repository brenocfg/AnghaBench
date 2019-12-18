#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct instruction {scalar_t__ type; scalar_t__ offset; scalar_t__ len; TYPE_2__* func; struct instruction* jump_dest; TYPE_1__* sec; scalar_t__ ignore; } ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ INSN_JUMP_UNCONDITIONAL ; 
 scalar_t__ INSN_NOP ; 
 scalar_t__ is_kasan_insn (struct instruction*) ; 
 scalar_t__ is_ubsan_insn (struct instruction*) ; 
 int /*<<< orphan*/  list ; 
 struct instruction* list_next_entry (struct instruction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool ignore_unreachable_insn(struct instruction *insn)
{
	int i;

	if (insn->ignore || insn->type == INSN_NOP)
		return true;

	/*
	 * Ignore any unused exceptions.  This can happen when a whitelisted
	 * function has an exception table entry.
	 *
	 * Also ignore alternative replacement instructions.  This can happen
	 * when a whitelisted function uses one of the ALTERNATIVE macros.
	 */
	if (!strcmp(insn->sec->name, ".fixup") ||
	    !strcmp(insn->sec->name, ".altinstr_replacement") ||
	    !strcmp(insn->sec->name, ".altinstr_aux"))
		return true;

	/*
	 * Check if this (or a subsequent) instruction is related to
	 * CONFIG_UBSAN or CONFIG_KASAN.
	 *
	 * End the search at 5 instructions to avoid going into the weeds.
	 */
	if (!insn->func)
		return false;
	for (i = 0; i < 5; i++) {

		if (is_kasan_insn(insn) || is_ubsan_insn(insn))
			return true;

		if (insn->type == INSN_JUMP_UNCONDITIONAL) {
			if (insn->jump_dest &&
			    insn->jump_dest->func == insn->func) {
				insn = insn->jump_dest;
				continue;
			}

			break;
		}

		if (insn->offset + insn->len >= insn->func->offset + insn->func->len)
			break;

		insn = list_next_entry(insn, list);
	}

	return false;
}