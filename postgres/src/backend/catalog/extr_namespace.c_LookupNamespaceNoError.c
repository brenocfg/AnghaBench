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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvokeNamespaceSearchHook (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (char const*,int) ; 
 int /*<<< orphan*/  myTempNamespace ; 
 scalar_t__ strcmp (char const*,char*) ; 

Oid
LookupNamespaceNoError(const char *nspname)
{
	/* check for pg_temp alias */
	if (strcmp(nspname, "pg_temp") == 0)
	{
		if (OidIsValid(myTempNamespace))
		{
			InvokeNamespaceSearchHook(myTempNamespace, true);
			return myTempNamespace;
		}

		/*
		 * Since this is used only for looking up existing objects, there is
		 * no point in trying to initialize the temp namespace here; and doing
		 * so might create problems for some callers. Just report "not found".
		 */
		return InvalidOid;
	}

	return get_namespace_oid(nspname, true);
}