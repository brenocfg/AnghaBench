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

/* Variables and functions */
 int /*<<< orphan*/  base_yyout ; 
 char* connection ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output_escaped_str (char*,int) ; 
 int questionmarks ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_prepare_statement(char *name, char *stmt)
{
	fprintf(base_yyout, "{ ECPGprepare(__LINE__, %s, %d, ", connection ? connection : "NULL", questionmarks);
	output_escaped_str(name, true);
	fputs(", ", base_yyout);
	output_escaped_str(stmt, true);
	fputs(");", base_yyout);
	whenever_action(2);
	free(name);
	if (connection != NULL)
		free(connection);
	connection = NULL;
}