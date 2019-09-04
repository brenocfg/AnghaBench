#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct symbol {scalar_t__ sec; scalar_t__ offset; } ;
struct rela {scalar_t__ sym; unsigned long addend; scalar_t__ type; } ;
struct objtool_file {int ignore_unreachables; TYPE_2__* rodata; int /*<<< orphan*/  insn_list; } ;
struct instruction {scalar_t__ sec; scalar_t__ offset; scalar_t__ type; int /*<<< orphan*/  len; TYPE_1__* jump_dest; scalar_t__ first_jump_src; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {scalar_t__ sym; } ;
struct TYPE_4__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ INSN_JUMP_DYNAMIC ; 
 scalar_t__ INSN_JUMP_UNCONDITIONAL ; 
 scalar_t__ R_X86_64_PC32 ; 
 struct rela* find_rela_by_dest (TYPE_2__*,unsigned long) ; 
 struct rela* find_rela_by_dest_range (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_symbol_containing (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  list ; 
 struct instruction* list_prev_entry (struct instruction*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rela *find_switch_table(struct objtool_file *file,
				      struct symbol *func,
				      struct instruction *insn)
{
	struct rela *text_rela, *rodata_rela;
	struct instruction *orig_insn = insn;
	unsigned long table_offset;

	/*
	 * Backward search using the @first_jump_src links, these help avoid
	 * much of the 'in between' code. Which avoids us getting confused by
	 * it.
	 */
	for (;
	     &insn->list != &file->insn_list &&
	     insn->sec == func->sec &&
	     insn->offset >= func->offset;

	     insn = insn->first_jump_src ?: list_prev_entry(insn, list)) {

		if (insn != orig_insn && insn->type == INSN_JUMP_DYNAMIC)
			break;

		/* allow small jumps within the range */
		if (insn->type == INSN_JUMP_UNCONDITIONAL &&
		    insn->jump_dest &&
		    (insn->jump_dest->offset <= insn->offset ||
		     insn->jump_dest->offset > orig_insn->offset))
		    break;

		/* look for a relocation which references .rodata */
		text_rela = find_rela_by_dest_range(insn->sec, insn->offset,
						    insn->len);
		if (!text_rela || text_rela->sym != file->rodata->sym)
			continue;

		table_offset = text_rela->addend;
		if (text_rela->type == R_X86_64_PC32)
			table_offset += 4;

		/*
		 * Make sure the .rodata address isn't associated with a
		 * symbol.  gcc jump tables are anonymous data.
		 */
		if (find_symbol_containing(file->rodata, table_offset))
			continue;

		rodata_rela = find_rela_by_dest(file->rodata, table_offset);
		if (rodata_rela) {
			/*
			 * Use of RIP-relative switch jumps is quite rare, and
			 * indicates a rare GCC quirk/bug which can leave dead
			 * code behind.
			 */
			if (text_rela->type == R_X86_64_PC32)
				file->ignore_unreachables = true;

			return rodata_rela;
		}
	}

	return NULL;
}