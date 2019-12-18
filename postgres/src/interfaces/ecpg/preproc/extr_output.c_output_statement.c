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
typedef  enum ECPG_statement_type { ____Placeholder_ECPG_statement_type } ECPG_statement_type ;

/* Variables and functions */
 int ECPGst_exec_immediate ; 
 int ECPGst_execute ; 
 int ECPGst_normal ; 
 int ECPGst_prepnormal ; 
 int /*<<< orphan*/  argsinsert ; 
 int /*<<< orphan*/  argsresult ; 
 int /*<<< orphan*/  auto_prepare ; 
 int /*<<< orphan*/  base_yyout ; 
 int compat ; 
 char* connection ; 
 int /*<<< orphan*/  dump_variables (int /*<<< orphan*/ ,int) ; 
 char** ecpg_statement_type_name ; 
 int force_indicator ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output_escaped_str (char*,int) ; 
 int questionmarks ; 
 int /*<<< orphan*/  reset_variables () ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_statement(char *stmt, int whenever_mode, enum ECPG_statement_type st)
{
	fprintf(base_yyout, "{ ECPGdo(__LINE__, %d, %d, %s, %d, ", compat, force_indicator, connection ? connection : "NULL", questionmarks);

	if (st == ECPGst_prepnormal && !auto_prepare)
		st = ECPGst_normal;

	/*
	 * In following cases, stmt is CSTRING or char_variable. They must be
	 * output directly. - prepared_name of EXECUTE without exprlist -
	 * execstring of EXECUTE IMMEDIATE
	 */
	fprintf(base_yyout, "%s, ", ecpg_statement_type_name[st]);
	if (st == ECPGst_execute || st == ECPGst_exec_immediate)
		fprintf(base_yyout, "%s, ", stmt);
	else
	{
		fputs("\"", base_yyout);
		output_escaped_str(stmt, false);
		fputs("\", ", base_yyout);
	}

	/* dump variables to C file */
	dump_variables(argsinsert, 1);
	fputs("ECPGt_EOIT, ", base_yyout);
	dump_variables(argsresult, 1);
	fputs("ECPGt_EORT);", base_yyout);
	reset_variables();

	whenever_action(whenever_mode | 2);
	free(stmt);
	if (connection != NULL)
		free(connection);
	connection = NULL;
}