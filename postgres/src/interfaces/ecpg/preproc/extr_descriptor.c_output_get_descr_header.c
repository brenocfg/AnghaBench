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
struct assignment {scalar_t__ value; int /*<<< orphan*/  variable; struct assignment* next; } ;

/* Variables and functions */
 scalar_t__ ECPGd_count ; 
 int /*<<< orphan*/  ECPGnumeric_lvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_WARNING ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 struct assignment* assignments ; 
 int /*<<< orphan*/  base_yyout ; 
 int /*<<< orphan*/  drop_assignments () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_get_descr_header(char *desc_name)
{
	struct assignment *results;

	fprintf(base_yyout, "{ ECPGget_desc_header(__LINE__, %s, &(", desc_name);
	for (results = assignments; results != NULL; results = results->next)
	{
		if (results->value == ECPGd_count)
			ECPGnumeric_lvalue(results->variable);
		else
			mmerror(PARSE_ERROR, ET_WARNING, "descriptor header item \"%d\" does not exist", results->value);
	}

	drop_assignments();
	fprintf(base_yyout, "));\n");
	whenever_action(3);
}