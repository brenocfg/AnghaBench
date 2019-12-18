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
struct ins {struct ins_ops* ops; } ;
struct arch {int nr_instructions; int sorted_instructions; int /*<<< orphan*/  instructions; } ;

/* Variables and functions */
 struct ins* bsearch (char const*,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ins__key_cmp ; 
 int /*<<< orphan*/  ins__sort (struct arch*) ; 

__attribute__((used)) static struct ins_ops *__ins__find(struct arch *arch, const char *name)
{
	struct ins *ins;
	const int nmemb = arch->nr_instructions;

	if (!arch->sorted_instructions) {
		ins__sort(arch);
		arch->sorted_instructions = true;
	}

	ins = bsearch(name, arch->instructions, nmemb, sizeof(struct ins), ins__key_cmp);
	return ins ? ins->ops : NULL;
}