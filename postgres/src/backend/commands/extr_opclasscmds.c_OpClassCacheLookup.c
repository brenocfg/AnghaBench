#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  amname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_am ;

/* Variables and functions */
 int /*<<< orphan*/  AMOID ; 
 int /*<<< orphan*/  CLAAMNAMENSP ; 
 int /*<<< orphan*/  CLAOID ; 
 int /*<<< orphan*/  DeconstructQualifiedName (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LookupExplicitNamespace (char*,int) ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpclassnameGetOpcid (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HeapTuple
OpClassCacheLookup(Oid amID, List *opclassname, bool missing_ok)
{
	char	   *schemaname;
	char	   *opcname;
	HeapTuple	htup;

	/* deconstruct the name list */
	DeconstructQualifiedName(opclassname, &schemaname, &opcname);

	if (schemaname)
	{
		/* Look in specific schema only */
		Oid			namespaceId;

		namespaceId = LookupExplicitNamespace(schemaname, missing_ok);
		if (!OidIsValid(namespaceId))
			htup = NULL;
		else
			htup = SearchSysCache3(CLAAMNAMENSP,
								   ObjectIdGetDatum(amID),
								   PointerGetDatum(opcname),
								   ObjectIdGetDatum(namespaceId));
	}
	else
	{
		/* Unqualified opclass name, so search the search path */
		Oid			opcID = OpclassnameGetOpcid(amID, opcname);

		if (!OidIsValid(opcID))
			htup = NULL;
		else
			htup = SearchSysCache1(CLAOID, ObjectIdGetDatum(opcID));
	}

	if (!HeapTupleIsValid(htup) && !missing_ok)
	{
		HeapTuple	amtup;

		amtup = SearchSysCache1(AMOID, ObjectIdGetDatum(amID));
		if (!HeapTupleIsValid(amtup))
			elog(ERROR, "cache lookup failed for access method %u", amID);
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("operator class \"%s\" does not exist for access method \"%s\"",
						NameListToString(opclassname),
						NameStr(((Form_pg_am) GETSTRUCT(amtup))->amname))));
	}

	return htup;
}