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
#define  ECPGd_cardinality 142 
#define  ECPGd_data 141 
#define  ECPGd_di_code 140 
#define  ECPGd_di_precision 139 
#define  ECPGd_indicator 138 
#define  ECPGd_key_member 137 
#define  ECPGd_length 136 
#define  ECPGd_name 135 
#define  ECPGd_nullable 134 
#define  ECPGd_octet 133 
#define  ECPGd_precision 132 
#define  ECPGd_ret_length 131 
#define  ECPGd_ret_octet 130 
#define  ECPGd_scale 129 
#define  ECPGd_type 128 
 int /*<<< orphan*/  ECPGdump_a_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 struct assignment* assignments ; 
 int /*<<< orphan*/  base_yyout ; 
 int /*<<< orphan*/  descriptor_item_name (int) ; 
 int /*<<< orphan*/  drop_assignments () ; 
 struct variable* find_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_dtype (int) ; 
 char* mm_strdup (char*) ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_set_descr(char *desc_name, char *index)
{
	struct assignment *results;

	fprintf(base_yyout, "{ ECPGset_desc(__LINE__, %s, %s,", desc_name, index);
	for (results = assignments; results != NULL; results = results->next)
	{
		const struct variable *v = find_variable(results->variable);

		switch (results->value)
		{
			case ECPGd_cardinality:
			case ECPGd_di_code:
			case ECPGd_di_precision:
			case ECPGd_precision:
			case ECPGd_scale:
				mmfatal(PARSE_ERROR, "descriptor item \"%s\" is not implemented",
						descriptor_item_name(results->value));
				break;

			case ECPGd_key_member:
			case ECPGd_name:
			case ECPGd_nullable:
			case ECPGd_octet:
			case ECPGd_ret_length:
			case ECPGd_ret_octet:
				mmfatal(PARSE_ERROR, "descriptor item \"%s\" cannot be set",
						descriptor_item_name(results->value));
				break;

			case ECPGd_data:
			case ECPGd_indicator:
			case ECPGd_length:
			case ECPGd_type:
				{
					char	   *str_zero = mm_strdup("0");

					fprintf(base_yyout, "%s,", get_dtype(results->value));
					ECPGdump_a_type(base_yyout, v->name, v->type, v->brace_level,
									NULL, NULL, -1, NULL, NULL, str_zero, NULL, NULL);
					free(str_zero);
				}
				break;

			default:
				;
		}
	}
	drop_assignments();
	fputs("ECPGd_EODT);\n", base_yyout);

	whenever_action(2 | 1);
}