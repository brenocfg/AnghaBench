#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_4__ {int /*<<< orphan*/  defname; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_1__ DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
#define  T_Float 132 
#define  T_Integer 131 
#define  T_List 130 
#define  T_String 129 
#define  T_TypeName 128 
 int /*<<< orphan*/  TypeNameToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defGetString (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int intVal (int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ *) ; 

int
defGetTypeLength(DefElem *def)
{
	if (def->arg == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("%s requires a parameter",
						def->defname)));
	switch (nodeTag(def->arg))
	{
		case T_Integer:
			return intVal(def->arg);
		case T_Float:
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("%s requires an integer value",
							def->defname)));
			break;
		case T_String:
			if (pg_strcasecmp(strVal(def->arg), "variable") == 0)
				return -1;		/* variable length */
			break;
		case T_TypeName:
			/* cope if grammar chooses to believe "variable" is a typename */
			if (pg_strcasecmp(TypeNameToString((TypeName *) def->arg),
							  "variable") == 0)
				return -1;		/* variable length */
			break;
		case T_List:
			/* must be an operator name */
			break;
		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(def->arg));
	}
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("invalid argument for %s: \"%s\"",
					def->defname, defGetString(def))));
	return 0;					/* keep compiler quiet */
}