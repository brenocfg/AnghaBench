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
struct ECPGtype {int dummy; } ;
struct ECPGstruct_member {struct ECPGstruct_member* next; struct ECPGtype* type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ mm_alloc (int) ; 
 int /*<<< orphan*/  mm_strdup (char const*) ; 

void
ECPGmake_struct_member(const char *name, struct ECPGtype *type, struct ECPGstruct_member **start)
{
	struct ECPGstruct_member *ptr,
			   *ne =
	(struct ECPGstruct_member *) mm_alloc(sizeof(struct ECPGstruct_member));

	ne->name = mm_strdup(name);
	ne->type = type;
	ne->next = NULL;

	for (ptr = *start; ptr && ptr->next; ptr = ptr->next);

	if (ptr)
		ptr->next = ne;
	else
		*start = ne;
}