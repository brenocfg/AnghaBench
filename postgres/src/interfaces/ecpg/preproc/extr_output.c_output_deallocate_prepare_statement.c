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
 int compat ; 
 char* connection ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output_escaped_str (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_deallocate_prepare_statement(char *name)
{
	const char *con = connection ? connection : "NULL";

	if (strcmp(name, "all") != 0)
	{
		fprintf(base_yyout, "{ ECPGdeallocate(__LINE__, %d, %s, ", compat, con);
		output_escaped_str(name, true);
		fputs(");", base_yyout);
	}
	else
		fprintf(base_yyout, "{ ECPGdeallocate_all(__LINE__, %d, %s);", compat, con);

	whenever_action(2);
	free(name);
	if (connection != NULL)
		free(connection);
	connection = NULL;
}