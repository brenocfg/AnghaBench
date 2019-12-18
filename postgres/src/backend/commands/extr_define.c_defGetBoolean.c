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
struct TYPE_4__ {int /*<<< orphan*/  defname; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_1__ DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
#define  T_Integer 128 
 char* defGetString (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intVal (int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_strcasecmp (char*,char*) ; 

bool
defGetBoolean(DefElem *def)
{
	/*
	 * If no parameter given, assume "true" is meant.
	 */
	if (def->arg == NULL)
		return true;

	/*
	 * Allow 0, 1, "true", "false", "on", "off"
	 */
	switch (nodeTag(def->arg))
	{
		case T_Integer:
			switch (intVal(def->arg))
			{
				case 0:
					return false;
				case 1:
					return true;
				default:
					/* otherwise, error out below */
					break;
			}
			break;
		default:
			{
				char	   *sval = defGetString(def);

				/*
				 * The set of strings accepted here should match up with the
				 * grammar's opt_boolean_or_string production.
				 */
				if (pg_strcasecmp(sval, "true") == 0)
					return true;
				if (pg_strcasecmp(sval, "false") == 0)
					return false;
				if (pg_strcasecmp(sval, "on") == 0)
					return true;
				if (pg_strcasecmp(sval, "off") == 0)
					return false;
			}
			break;
	}
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("%s requires a Boolean value",
					def->defname)));
	return false;				/* keep compiler quiet */
}