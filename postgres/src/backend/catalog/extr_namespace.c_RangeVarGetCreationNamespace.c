#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ relpersistence; scalar_t__ schemaname; int /*<<< orphan*/  relname; scalar_t__ catalogname; } ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessTempTableNamespace (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_SCHEMA ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELPERSISTENCE_TEMP ; 
 int /*<<< orphan*/  activeCreationNamespace ; 
 scalar_t__ activeTempCreationPending ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (scalar_t__,int) ; 
 int /*<<< orphan*/  myTempNamespace ; 
 int /*<<< orphan*/  recomputeNamespacePath () ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

Oid
RangeVarGetCreationNamespace(const RangeVar *newRelation)
{
	Oid			namespaceId;

	/*
	 * We check the catalog name and then ignore it.
	 */
	if (newRelation->catalogname)
	{
		if (strcmp(newRelation->catalogname, get_database_name(MyDatabaseId)) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cross-database references are not implemented: \"%s.%s.%s\"",
							newRelation->catalogname, newRelation->schemaname,
							newRelation->relname)));
	}

	if (newRelation->schemaname)
	{
		/* check for pg_temp alias */
		if (strcmp(newRelation->schemaname, "pg_temp") == 0)
		{
			/* Initialize temp namespace */
			AccessTempTableNamespace(false);
			return myTempNamespace;
		}
		/* use exact schema given */
		namespaceId = get_namespace_oid(newRelation->schemaname, false);
		/* we do not check for USAGE rights here! */
	}
	else if (newRelation->relpersistence == RELPERSISTENCE_TEMP)
	{
		/* Initialize temp namespace */
		AccessTempTableNamespace(false);
		return myTempNamespace;
	}
	else
	{
		/* use the default creation namespace */
		recomputeNamespacePath();
		if (activeTempCreationPending)
		{
			/* Need to initialize temp namespace */
			AccessTempTableNamespace(true);
			return myTempNamespace;
		}
		namespaceId = activeCreationNamespace;
		if (!OidIsValid(namespaceId))
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_SCHEMA),
					 errmsg("no schema has been selected to create in")));
	}

	/* Note: callers will check for CREATE rights when appropriate */

	return namespaceId;
}