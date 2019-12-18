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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessTempTableNamespace (int) ; 
 int /*<<< orphan*/  DeconstructQualifiedName (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_SCHEMA ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activeCreationNamespace ; 
 scalar_t__ activeTempCreationPending ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_namespace_oid (char*,int) ; 
 int /*<<< orphan*/  myTempNamespace ; 
 int /*<<< orphan*/  recomputeNamespacePath () ; 
 scalar_t__ strcmp (char*,char*) ; 

Oid
QualifiedNameGetCreationNamespace(List *names, char **objname_p)
{
	char	   *schemaname;
	Oid			namespaceId;

	/* deconstruct the name list */
	DeconstructQualifiedName(names, &schemaname, objname_p);

	if (schemaname)
	{
		/* check for pg_temp alias */
		if (strcmp(schemaname, "pg_temp") == 0)
		{
			/* Initialize temp namespace */
			AccessTempTableNamespace(false);
			return myTempNamespace;
		}
		/* use exact schema given */
		namespaceId = get_namespace_oid(schemaname, false);
		/* we do not check for USAGE rights here! */
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

	return namespaceId;
}