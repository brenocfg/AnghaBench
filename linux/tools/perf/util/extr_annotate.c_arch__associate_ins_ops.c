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
struct ins {struct ins_ops* ops; int /*<<< orphan*/  name; } ;
struct arch {size_t nr_instructions; size_t nr_instructions_allocated; struct ins* instructions; } ;

/* Variables and functions */
 scalar_t__ arch__grow_instructions (struct arch*) ; 
 int /*<<< orphan*/  ins__sort (struct arch*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int arch__associate_ins_ops(struct arch* arch, const char *name, struct ins_ops *ops)
{
	struct ins *ins;

	if (arch->nr_instructions == arch->nr_instructions_allocated &&
	    arch__grow_instructions(arch))
		return -1;

	ins = &arch->instructions[arch->nr_instructions];
	ins->name = strdup(name);
	if (!ins->name)
		return -1;

	ins->ops  = ops;
	arch->nr_instructions++;

	ins__sort(arch);
	return 0;
}