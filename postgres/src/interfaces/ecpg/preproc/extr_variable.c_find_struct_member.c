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
struct variable {int dummy; } ;
struct ECPGstruct_member {TYPE_5__* type; int /*<<< orphan*/  name; struct ECPGstruct_member* next; } ;
struct TYPE_9__ {struct ECPGstruct_member* members; TYPE_3__* element; } ;
struct TYPE_10__ {int type; TYPE_4__ u; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; int /*<<< orphan*/  struct_sizeof; int /*<<< orphan*/  type_name; } ;
struct TYPE_7__ {struct ECPGstruct_member* members; TYPE_1__* element; } ;
struct TYPE_8__ {int type; TYPE_2__ u; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; int /*<<< orphan*/  struct_sizeof; int /*<<< orphan*/  type_name; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGmake_array_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGmake_simple_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGmake_struct_type (struct ECPGstruct_member*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ECPGt_array 130 
#define  ECPGt_struct 129 
#define  ECPGt_union 128 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*,char*) ; 
 struct variable* new_variable (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static struct variable *
find_struct_member(char *name, char *str, struct ECPGstruct_member *members, int brace_level)
{
	char	   *next = strpbrk(++str, ".-["),
			   *end,
				c = '\0';

	if (next != NULL)
	{
		c = *next;
		*next = '\0';
	}

	for (; members; members = members->next)
	{
		if (strcmp(members->name, str) == 0)
		{
			if (next == NULL)
			{
				/* found the end */
				switch (members->type->type)
				{
					case ECPGt_array:
						return new_variable(name, ECPGmake_array_type(ECPGmake_simple_type(members->type->u.element->type, members->type->u.element->size, members->type->u.element->counter), members->type->size), brace_level);
					case ECPGt_struct:
					case ECPGt_union:
						return new_variable(name, ECPGmake_struct_type(members->type->u.members, members->type->type, members->type->type_name, members->type->struct_sizeof), brace_level);
					default:
						return new_variable(name, ECPGmake_simple_type(members->type->type, members->type->size, members->type->counter), brace_level);
				}
			}
			else
			{
				*next = c;
				if (c == '[')
				{
					int			count;

					/*
					 * We don't care about what's inside the array braces so
					 * just eat up the character
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
				}
				else
					end = next;

				switch (*end)
				{
					case '\0':	/* found the end, but this time it has to be
								 * an array element */
						if (members->type->type != ECPGt_array)
							mmfatal(PARSE_ERROR, "incorrectly formed variable \"%s\"", name);

						switch (members->type->u.element->type)
						{
							case ECPGt_array:
								return new_variable(name, ECPGmake_array_type(ECPGmake_simple_type(members->type->u.element->u.element->type, members->type->u.element->u.element->size, members->type->u.element->u.element->counter), members->type->u.element->size), brace_level);
							case ECPGt_struct:
							case ECPGt_union:
								return new_variable(name, ECPGmake_struct_type(members->type->u.element->u.members, members->type->u.element->type, members->type->u.element->type_name, members->type->u.element->struct_sizeof), brace_level);
							default:
								return new_variable(name, ECPGmake_simple_type(members->type->u.element->type, members->type->u.element->size, members->type->u.element->counter), brace_level);
						}
						break;
					case '-':
						if (members->type->type == ECPGt_array)
							return find_struct_member(name, ++end, members->type->u.element->u.members, brace_level);
						else
							return find_struct_member(name, ++end, members->type->u.members, brace_level);
						break;
						break;
					case '.':
						if (members->type->type == ECPGt_array)
							return find_struct_member(name, end, members->type->u.element->u.members, brace_level);
						else
							return find_struct_member(name, end, members->type->u.members, brace_level);
						break;
					default:
						mmfatal(PARSE_ERROR, "incorrectly formed variable \"%s\"", name);
						break;
				}
			}
		}
	}

	return NULL;
}