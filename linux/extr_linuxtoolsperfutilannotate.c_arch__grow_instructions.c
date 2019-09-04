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
struct ins {int dummy; } ;
struct arch {int nr_instructions_allocated; int nr_instructions; struct ins* instructions; } ;

/* Variables and functions */
 struct ins* calloc (size_t,int) ; 
 int /*<<< orphan*/  memcpy (struct ins*,struct ins*,int) ; 
 struct ins* realloc (struct ins*,size_t) ; 

__attribute__((used)) static int arch__grow_instructions(struct arch *arch)
{
	struct ins *new_instructions;
	size_t new_nr_allocated;

	if (arch->nr_instructions_allocated == 0 && arch->instructions)
		goto grow_from_non_allocated_table;

	new_nr_allocated = arch->nr_instructions_allocated + 128;
	new_instructions = realloc(arch->instructions, new_nr_allocated * sizeof(struct ins));
	if (new_instructions == NULL)
		return -1;

out_update_instructions:
	arch->instructions = new_instructions;
	arch->nr_instructions_allocated = new_nr_allocated;
	return 0;

grow_from_non_allocated_table:
	new_nr_allocated = arch->nr_instructions + 128;
	new_instructions = calloc(new_nr_allocated, sizeof(struct ins));
	if (new_instructions == NULL)
		return -1;

	memcpy(new_instructions, arch->instructions, arch->nr_instructions);
	goto out_update_instructions;
}