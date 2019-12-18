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
 struct ins_ops jump_ops ; 
 struct ins_ops ret_ops ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static struct ins_ops *csky__associate_ins_ops(struct arch *arch,
					       const char *name)
{
	struct ins_ops *ops = NULL;

	/* catch all kind of jumps */
	if (!strcmp(name, "bt") ||
	    !strcmp(name, "bf") ||
	    !strcmp(name, "bez") ||
	    !strcmp(name, "bnez") ||
	    !strcmp(name, "bnezad") ||
	    !strcmp(name, "bhsz") ||
	    !strcmp(name, "bhz") ||
	    !strcmp(name, "blsz") ||
	    !strcmp(name, "blz") ||
	    !strcmp(name, "br") ||
	    !strcmp(name, "jmpi") ||
	    !strcmp(name, "jmp"))
		ops = &jump_ops;

	/* catch function call */
	if (!strcmp(name, "bsr") ||
	    !strcmp(name, "jsri") ||
	    !strcmp(name, "jsr"))
		ops = &call_ops;

	/* catch function return */
	if (!strcmp(name, "rts"))
		ops = &ret_ops;

	if (ops)
		arch__associate_ins_ops(arch, name, ops);
	return ops;
}