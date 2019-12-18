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
struct ins_ops {int dummy; } ;
struct arch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch__associate_ins_ops (struct arch*,char const*,struct ins_ops*) ; 
 struct ins_ops call_ops ; 
 scalar_t__ is_branch_cond (char const*) ; 
 scalar_t__ is_branch_float_cond (char const*) ; 
 scalar_t__ is_branch_reg_cond (char const*) ; 
 struct ins_ops jump_ops ; 
 struct ins_ops mov_ops ; 
 struct ins_ops ret_ops ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static struct ins_ops *sparc__associate_instruction_ops(struct arch *arch, const char *name)
{
	struct ins_ops *ops = NULL;

	if (!strcmp(name, "call") ||
	    !strcmp(name, "jmp") ||
	    !strcmp(name, "jmpl")) {
		ops = &call_ops;
	} else if (!strcmp(name, "ret") ||
		   !strcmp(name, "retl") ||
		   !strcmp(name, "return")) {
		ops = &ret_ops;
	} else if (!strcmp(name, "mov")) {
		ops = &mov_ops;
	} else {
		if (name[0] == 'c' &&
		    (name[1] == 'w' || name[1] == 'x'))
			name += 2;

		if (name[0] == 'b') {
			const char *cond = name + 1;

			if (cond[0] == 'r') {
				if (is_branch_reg_cond(cond + 1))
					ops = &jump_ops;
			} else if (is_branch_cond(cond)) {
				ops = &jump_ops;
			}
		} else if (name[0] == 'f' && name[1] == 'b') {
			if (is_branch_float_cond(name + 2))
				ops = &jump_ops;
		}
	}

	if (ops)
		arch__associate_ins_ops(arch, name, ops);

	return ops;
}