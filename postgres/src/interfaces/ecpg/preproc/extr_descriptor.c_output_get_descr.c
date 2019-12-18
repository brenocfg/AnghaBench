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
struct variable {int /*<<< orphan*/  brace_level; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct assignment {int value; int /*<<< orphan*/  variable; struct assignment* next; } ;

/* Variables and functions */
#define  ECPGd_key_member 129 
#define  ECPGd_nullable 128 
 int /*<<< orphan*/  ECPGdump_a_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ET_WARNING ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 struct assignment* assignments ; 
 int /*<<< orphan*/  base_yyout ; 
 int /*<<< orphan*/  drop_assignments () ; 
 struct variable* find_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_dtype (int) ; 
 char* mm_strdup (char*) ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_get_descr(char *desc_name, char *index)
{
	struct assignment *results;

	fprintf(base_yyout, "{ ECPGget_desc(__LINE__, %s, %s,", desc_name, index);
	for (results = assignments; results != NULL; results = results->next)
	{
		const struct variable *v = find_variable(results->variable);
		char	   *str_zero = mm_strdup("0");

		switch (results->value)
		{
			case ECPGd_nullable:
				mmerror(PARSE_ERROR, ET_WARNING, "nullable is always 1");
				break;
			case ECPGd_key_member:
				mmerror(PARSE_ERROR, ET_WARNING, "key_member is always 0");
				break;
			default:
				break;
		}
		fprintf(base_yyout, "%s,", get_dtype(results->value));
		ECPGdump_a_type(base_yyout, v->name, v->type, v->brace_level,
						NULL, NULL, -1, NULL, NULL, str_zero, NULL, NULL);
		free(str_zero);
	}
	drop_assignments();
	fputs("ECPGd_EODT);\n", base_yyout);

	whenever_action(2 | 1);
}