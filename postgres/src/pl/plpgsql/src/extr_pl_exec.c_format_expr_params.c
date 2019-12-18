#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_17__ {scalar_t__* datums; } ;
struct TYPE_16__ {int /*<<< orphan*/  paramnos; } ;
struct TYPE_15__ {int /*<<< orphan*/  refname; } ;
struct TYPE_14__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ PLpgSQL_var ;
typedef  TYPE_3__ PLpgSQL_expr ;
typedef  TYPE_4__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  PLpgSQL_datum ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoCharMacro (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 char* convert_value_to_string (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_eval_datum (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_eval_mcontext (TYPE_4__*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

__attribute__((used)) static char *
format_expr_params(PLpgSQL_execstate *estate,
				   const PLpgSQL_expr *expr)
{
	int			paramno;
	int			dno;
	StringInfoData paramstr;
	MemoryContext oldcontext;

	if (!expr->paramnos)
		return NULL;

	oldcontext = MemoryContextSwitchTo(get_eval_mcontext(estate));

	initStringInfo(&paramstr);
	paramno = 0;
	dno = -1;
	while ((dno = bms_next_member(expr->paramnos, dno)) >= 0)
	{
		Datum		paramdatum;
		Oid			paramtypeid;
		bool		paramisnull;
		int32		paramtypmod;
		PLpgSQL_var *curvar;

		curvar = (PLpgSQL_var *) estate->datums[dno];

		exec_eval_datum(estate, (PLpgSQL_datum *) curvar,
						&paramtypeid, &paramtypmod,
						&paramdatum, &paramisnull);

		appendStringInfo(&paramstr, "%s%s = ",
						 paramno > 0 ? ", " : "",
						 curvar->refname);

		if (paramisnull)
			appendStringInfoString(&paramstr, "NULL");
		else
		{
			char	   *value = convert_value_to_string(estate, paramdatum, paramtypeid);
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

		paramno++;
	}

	MemoryContextSwitchTo(oldcontext);

	return paramstr.data;
}