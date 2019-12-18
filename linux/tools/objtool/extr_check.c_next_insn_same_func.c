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
struct symbol {int /*<<< orphan*/  offset; struct symbol* cfunc; int /*<<< orphan*/  sec; } ;
struct objtool_file {int /*<<< orphan*/  insn_list; } ;
struct instruction {struct symbol* func; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct instruction* find_insn (struct objtool_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 struct instruction* list_next_entry (struct instruction*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct instruction *next_insn_same_func(struct objtool_file *file,
					       struct instruction *insn)
{
	struct instruction *next = list_next_entry(insn, list);
	struct symbol *func = insn->func;

	if (!func)
		return NULL;

	if (&next->list != &file->insn_list && next->func == func)
		return next;

	/* Check if we're already in the subfunction: */
	if (func == func->cfunc)
		return NULL;

	/* Move to the subfunction: */
	return find_insn(file, func->cfunc->sec, func->cfunc->offset);
}