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
struct config_generic {int flags; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ROLE_READ_ALL_SETTINGS ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int GUC_SUPERUSER_ONLY ; 
 int /*<<< orphan*/  GetUserId () ; 
 char* _ShowOption (struct config_generic*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 struct config_generic* find_option (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
GetConfigOptionByName(const char *name, const char **varname, bool missing_ok)
{
	struct config_generic *record;

	record = find_option(name, false, ERROR);
	if (record == NULL)
	{
		if (missing_ok)
		{
			if (varname)
				*varname = NULL;
			return NULL;
		}

		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("unrecognized configuration parameter \"%s\"", name)));
	}

	if ((record->flags & GUC_SUPERUSER_ONLY) &&
		!is_member_of_role(GetUserId(), DEFAULT_ROLE_READ_ALL_SETTINGS))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser or a member of pg_read_all_settings to examine \"%s\"",
						name)));

	if (varname)
		*varname = record->name;

	return _ShowOption(record, true);
}