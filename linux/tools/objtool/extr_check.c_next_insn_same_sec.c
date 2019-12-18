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
struct objtool_file {int /*<<< orphan*/  insn_list; } ;
struct instruction {scalar_t__ sec; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list ; 
 struct instruction* list_next_entry (struct instruction*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct instruction *next_insn_same_sec(struct objtool_file *file,
					      struct instruction *insn)
{
	struct instruction *next = list_next_entry(insn, list);

	if (!next || &next->list == &file->insn_list || next->sec != insn->sec)
		return NULL;

	return next;
}