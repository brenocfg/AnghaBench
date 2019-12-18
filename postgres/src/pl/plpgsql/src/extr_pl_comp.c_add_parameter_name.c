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
typedef  int /*<<< orphan*/  PLpgSQL_nsitem_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  plpgsql_ns_additem (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/ * plpgsql_ns_lookup (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_ns_top () ; 

__attribute__((used)) static void
add_parameter_name(PLpgSQL_nsitem_type itemtype, int itemno, const char *name)
{
	/*
	 * Before adding the name, check for duplicates.  We need this even though
	 * functioncmds.c has a similar check, because that code explicitly
	 * doesn't complain about conflicting IN and OUT parameter names.  In
	 * plpgsql, such names are in the same namespace, so there is no way to
	 * disambiguate.
	 */
	if (plpgsql_ns_lookup(plpgsql_ns_top(), true,
						  name, NULL, NULL,
						  NULL) != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
				 errmsg("parameter name \"%s\" used more than once",
						name)));

	/* OK, add the name */
	plpgsql_ns_additem(itemtype, itemno, name);
}