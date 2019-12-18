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
struct typedefs {int brace_level; scalar_t__ type_enum; struct typedefs* next; struct typedefs* name; struct typedefs* type; struct typedefs* struct_member_list; } ;

/* Variables and functions */
 scalar_t__ ECPGt_struct ; 
 scalar_t__ ECPGt_union ; 
 int /*<<< orphan*/  free (struct typedefs*) ; 
 struct typedefs* types ; 

void
remove_typedefs(int brace_level)
{
	struct typedefs *p,
			   *prev;

	for (p = prev = types; p;)
	{
		if (p->brace_level >= brace_level)
		{
			/* remove it */
			if (p == types)
				prev = types = p->next;
			else
				prev->next = p->next;

			if (p->type->type_enum == ECPGt_struct || p->type->type_enum == ECPGt_union)
				free(p->struct_member_list);
			free(p->type);
			free(p->name);
			free(p);
			if (prev == types)
				p = types;
			else
				p = prev ? prev->next : NULL;
		}
		else
		{
			prev = p;
			p = prev->next;
		}
	}
}