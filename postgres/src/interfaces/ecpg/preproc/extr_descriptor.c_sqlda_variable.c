#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct variable {int /*<<< orphan*/ * next; scalar_t__ brace_level; struct ECPGtype* type; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * element; } ;
struct ECPGtype {scalar_t__ counter; TYPE_1__ u; int /*<<< orphan*/ * struct_sizeof; int /*<<< orphan*/ * size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGt_sqlda ; 
 scalar_t__ mm_alloc (int) ; 
 int /*<<< orphan*/  mm_strdup (char const*) ; 

struct variable *
sqlda_variable(const char *name)
{
	struct variable *p = (struct variable *) mm_alloc(sizeof(struct variable));

	p->name = mm_strdup(name);
	p->type = (struct ECPGtype *) mm_alloc(sizeof(struct ECPGtype));
	p->type->type = ECPGt_sqlda;
	p->type->size = NULL;
	p->type->struct_sizeof = NULL;
	p->type->u.element = NULL;
	p->type->counter = 0;
	p->brace_level = 0;
	p->next = NULL;

	return p;
}