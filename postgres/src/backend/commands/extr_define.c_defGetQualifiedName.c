#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * names; } ;
typedef  TYPE_1__ TypeName ;
struct TYPE_5__ {int /*<<< orphan*/  defname; int /*<<< orphan*/ * arg; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
#define  T_List 130 
#define  T_String 129 
#define  T_TypeName 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

List *
defGetQualifiedName(DefElem *def)
{
	if (def->arg == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("%s requires a parameter",
						def->defname)));
	switch (nodeTag(def->arg))
	{
		case T_TypeName:
			return ((TypeName *) def->arg)->names;
		case T_List:
			return (List *) def->arg;
		case T_String:
			/* Allow quoted name for backwards compatibility */
			return list_make1(def->arg);
		default:
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("argument of %s must be a name",
							def->defname)));
	}
	return NIL;					/* keep compiler quiet */
}