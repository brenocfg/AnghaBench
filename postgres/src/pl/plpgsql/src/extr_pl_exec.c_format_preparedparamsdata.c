#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nargs; char* nulls; int /*<<< orphan*/ * types; int /*<<< orphan*/ * values; } ;
struct TYPE_8__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ PreparedParamsData ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  appendStringInfoCharMacro (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 char* convert_value_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_eval_mcontext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

__attribute__((used)) static char *
format_preparedparamsdata(PLpgSQL_execstate *estate,
						  const PreparedParamsData *ppd)
{
	int			paramno;
	StringInfoData paramstr;
	MemoryContext oldcontext;

	if (!ppd)
		return NULL;

	oldcontext = MemoryContextSwitchTo(get_eval_mcontext(estate));

	initStringInfo(&paramstr);
	for (paramno = 0; paramno < ppd->nargs; paramno++)
	{
		appendStringInfo(&paramstr, "%s$%d = ",
						 paramno > 0 ? ", " : "",
						 paramno + 1);

		if (ppd->nulls[paramno] == 'n')
			appendStringInfoString(&paramstr, "NULL");
		else
		{
			char	   *value = convert_value_to_string(estate, ppd->values[paramno], ppd->types[paramno]);
			char	   *p;

			appendStringInfoCharMacro(&paramstr, '\'');
			for (p = value; *p; p++)
			{
				if (*p == '\'') /* double single quotes */
					appendStringInfoCharMacro(&paramstr, *p);
				appendStringInfoCharMacro(&paramstr, *p);
			}
			appendStringInfoCharMacro(&paramstr, '\'');
		}
	}

	MemoryContextSwitchTo(oldcontext);

	return paramstr.data;
}