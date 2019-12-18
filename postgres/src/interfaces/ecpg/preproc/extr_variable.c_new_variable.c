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
struct variable {int brace_level; struct variable* next; struct ECPGtype* type; int /*<<< orphan*/  name; } ;
struct ECPGtype {int dummy; } ;

/* Variables and functions */
 struct variable* allvariables ; 
 scalar_t__ mm_alloc (int) ; 
 int /*<<< orphan*/  mm_strdup (char const*) ; 

struct variable *
new_variable(const char *name, struct ECPGtype *type, int brace_level)
{
	struct variable *p = (struct variable *) mm_alloc(sizeof(struct variable));

	p->name = mm_strdup(name);
	p->type = type;
	p->brace_level = brace_level;

	p->next = allvariables;
	allvariables = p;

	return p;
}