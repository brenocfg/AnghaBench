#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct variable {int /*<<< orphan*/  brace_level; TYPE_5__* type; } ;
struct TYPE_9__ {TYPE_3__* element; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  members; TYPE_1__* element; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; int /*<<< orphan*/  struct_sizeof; int /*<<< orphan*/  type_name; TYPE_2__ u; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGmake_array_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGmake_simple_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGmake_struct_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ECPGt_array 130 
#define  ECPGt_struct 129 
#define  ECPGt_union 128 
 int /*<<< orphan*/  PARSE_ERROR ; 
 struct variable* find_simple (char*) ; 
 struct variable* find_struct (char*,char*,char*) ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*,char*) ; 
 struct variable* new_variable (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strpbrk (char*,char*) ; 

struct variable *
find_variable(char *name)
{
	char	   *next,
			   *end;
	struct variable *p;
	int			count;

	next = strpbrk(name, ".[-");
	if (next)
	{
		if (*next == '[')
		{
			/*
			 * We don't care about what's inside the array braces so just eat
			 * up the characters
			 */
			for (count = 1, end = next + 1; count; end++)
			{
				switch (*end)
				{
					case '[':
						count++;
						break;
					case ']':
						count--;
						break;
					default:
						break;
				}
			}
			if (*end == '.')
				p = find_struct(name, next, end);
			else
			{
				char		c = *next;

				*next = '\0';
				p = find_simple(name);
				if (p == NULL)
					mmfatal(PARSE_ERROR, "variable \"%s\" is not declared", name);

				*next = c;
				switch (p->type->u.element->type)
				{
					case ECPGt_array:
						return new_variable(name, ECPGmake_array_type(ECPGmake_simple_type(p->type->u.element->u.element->type, p->type->u.element->u.element->size, p->type->u.element->u.element->counter), p->type->u.element->size), p->brace_level);
					case ECPGt_struct:
					case ECPGt_union:
						return new_variable(name, ECPGmake_struct_type(p->type->u.element->u.members, p->type->u.element->type, p->type->u.element->type_name, p->type->u.element->struct_sizeof), p->brace_level);
					default:
						return new_variable(name, ECPGmake_simple_type(p->type->u.element->type, p->type->u.element->size, p->type->u.element->counter), p->brace_level);
				}
			}
		}
		else
			p = find_struct(name, next, next);
	}
	else
		p = find_simple(name);

	if (p == NULL)
		mmfatal(PARSE_ERROR, "variable \"%s\" is not declared", name);

	return p;
}