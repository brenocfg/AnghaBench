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
struct config_string {int /*<<< orphan*/ * variable; int /*<<< orphan*/  boot_val; } ;
struct config_real {int /*<<< orphan*/ * variable; int /*<<< orphan*/  boot_val; } ;
struct config_int {int /*<<< orphan*/ * variable; int /*<<< orphan*/  boot_val; } ;
struct config_generic {int flags; int vartype; } ;
struct config_enum {int /*<<< orphan*/ * variable; int /*<<< orphan*/  boot_val; } ;
struct config_bool {int /*<<< orphan*/ * variable; int /*<<< orphan*/  boot_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEFAULT_ROLE_READ_ALL_SETTINGS ; 
 int /*<<< orphan*/  ERROR ; 
 int GUC_EXPLAIN ; 
 int GUC_NO_SHOW_ALL ; 
 int GUC_SUPERUSER_ONLY ; 
 int /*<<< orphan*/  GetUserId () ; 
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 struct config_generic** guc_variables ; 
 int /*<<< orphan*/  is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_guc_explain_variables ; 
 int num_guc_variables ; 
 struct config_generic** palloc (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct config_generic **
get_explain_guc_options(int *num)
{
	int			i;
	struct config_generic **result;

	*num = 0;

	/*
	 * Allocate enough space to fit all GUC_EXPLAIN options. We may not need
	 * all the space, but there are fairly few such options so we don't waste
	 * a lot of memory.
	 */
	result = palloc(sizeof(struct config_generic *) * num_guc_explain_variables);

	for (i = 0; i < num_guc_variables; i++)
	{
		bool		modified;
		struct config_generic *conf = guc_variables[i];

		/* return only options visible to the user */
		if ((conf->flags & GUC_NO_SHOW_ALL) ||
			((conf->flags & GUC_SUPERUSER_ONLY) &&
			 !is_member_of_role(GetUserId(), DEFAULT_ROLE_READ_ALL_SETTINGS)))
			continue;

		/* only parameters explicitly marked for inclusion in explain */
		if (!(conf->flags & GUC_EXPLAIN))
			continue;

		/* return only options that were modified (w.r.t. config file) */
		modified = false;

		switch (conf->vartype)
		{
			case PGC_BOOL:
				{
					struct config_bool *lconf = (struct config_bool *) conf;

					modified = (lconf->boot_val != *(lconf->variable));
				}
				break;

			case PGC_INT:
				{
					struct config_int *lconf = (struct config_int *) conf;

					modified = (lconf->boot_val != *(lconf->variable));
				}
				break;

			case PGC_REAL:
				{
					struct config_real *lconf = (struct config_real *) conf;

					modified = (lconf->boot_val != *(lconf->variable));
				}
				break;

			case PGC_STRING:
				{
					struct config_string *lconf = (struct config_string *) conf;

					modified = (strcmp(lconf->boot_val, *(lconf->variable)) != 0);
				}
				break;

			case PGC_ENUM:
				{
					struct config_enum *lconf = (struct config_enum *) conf;

					modified = (lconf->boot_val != *(lconf->variable));
				}
				break;

			default:
				elog(ERROR, "unexpected GUC type: %d", conf->vartype);
		}

		/* skip GUC variables that match the built-in default */
		if (!modified)
			continue;

		/* assign to the values array */
		result[*num] = conf;
		*num = *num + 1;

		Assert(*num <= num_guc_explain_variables);
	}

	return result;
}