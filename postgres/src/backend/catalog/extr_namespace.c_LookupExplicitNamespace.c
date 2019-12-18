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
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvokeNamespaceSearchHook (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_namespace_oid (char const*,int) ; 
 int /*<<< orphan*/  myTempNamespace ; 
 scalar_t__ pg_namespace_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

Oid
LookupExplicitNamespace(const char *nspname, bool missing_ok)
{
	Oid			namespaceId;
	AclResult	aclresult;

	/* check for pg_temp alias */
	if (strcmp(nspname, "pg_temp") == 0)
	{
		if (OidIsValid(myTempNamespace))
			return myTempNamespace;

		/*
		 * Since this is used only for looking up existing objects, there is
		 * no point in trying to initialize the temp namespace here; and doing
		 * so might create problems for some callers --- just fall through.
		 */
	}

	namespaceId = get_namespace_oid(nspname, missing_ok);
	if (missing_ok && !OidIsValid(namespaceId))
		return InvalidOid;

	aclresult = pg_namespace_aclcheck(namespaceId, GetUserId(), ACL_USAGE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_SCHEMA,
					   nspname);
	/* Schema search hook for this lookup */
	InvokeNamespaceSearchHook(namespaceId, true);

	return namespaceId;
}