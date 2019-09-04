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
 struct ins_ops jump_ops ; 
 struct ins_ops ret_ops ; 
 struct ins_ops s390_call_ops ; 
 struct ins_ops s390_mov_ops ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static struct ins_ops *s390__associate_ins_ops(struct arch *arch, const char *name)
{
	struct ins_ops *ops = NULL;

	/* catch all kind of jumps */
	if (strchr(name, 'j') ||
	    !strncmp(name, "bct", 3) ||
	    !strncmp(name, "br", 2))
		ops = &jump_ops;
	/* override call/returns */
	if (!strcmp(name, "bras") ||
	    !strcmp(name, "brasl") ||
	    !strcmp(name, "basr"))
		ops = &s390_call_ops;
	if (!strcmp(name, "br"))
		ops = &ret_ops;
	/* override load/store relative to PC */
	if (!strcmp(name, "lrl") ||
	    !strcmp(name, "lgrl") ||
	    !strcmp(name, "lgfrl") ||
	    !strcmp(name, "llgfrl") ||
	    !strcmp(name, "strl") ||
	    !strcmp(name, "stgrl"))
		ops = &s390_mov_ops;

	if (ops)
		arch__associate_ins_ops(arch, name, ops);
	return ops;
}