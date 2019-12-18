#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* parentParseState; } ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupNamespaceNoError (char const*) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relname_relid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scanNameSpaceForRefname (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/ * scanNameSpaceForRelid (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

RangeTblEntry *
refnameRangeTblEntry(ParseState *pstate,
					 const char *schemaname,
					 const char *refname,
					 int location,
					 int *sublevels_up)
{
	Oid			relId = InvalidOid;

	if (sublevels_up)
		*sublevels_up = 0;

	if (schemaname != NULL)
	{
		Oid			namespaceId;

		/*
		 * We can use LookupNamespaceNoError() here because we are only
		 * interested in finding existing RTEs.  Checking USAGE permission on
		 * the schema is unnecessary since it would have already been checked
		 * when the RTE was made.  Furthermore, we want to report "RTE not
		 * found", not "no permissions for schema", if the name happens to
		 * match a schema name the user hasn't got access to.
		 */
		namespaceId = LookupNamespaceNoError(schemaname);
		if (!OidIsValid(namespaceId))
			return NULL;
		relId = get_relname_relid(refname, namespaceId);
		if (!OidIsValid(relId))
			return NULL;
	}

	while (pstate != NULL)
	{
		RangeTblEntry *result;

		if (OidIsValid(relId))
			result = scanNameSpaceForRelid(pstate, relId, location);
		else
			result = scanNameSpaceForRefname(pstate, refname, location);

		if (result)
			return result;

		if (sublevels_up)
			(*sublevels_up)++;
		else
			break;

		pstate = pstate->parentParseState;
	}
	return NULL;
}