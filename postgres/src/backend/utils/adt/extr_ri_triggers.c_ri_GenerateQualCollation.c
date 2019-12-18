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
struct TYPE_2__ {int /*<<< orphan*/  collnamespace; int /*<<< orphan*/  collname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_collation ;

/* Variables and functions */
 int /*<<< orphan*/  COLLOID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int MAX_QUOTED_NAME_LEN ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quoteOneName (char*,char*) ; 

__attribute__((used)) static void
ri_GenerateQualCollation(StringInfo buf, Oid collation)
{
	HeapTuple	tp;
	Form_pg_collation colltup;
	char	   *collname;
	char		onename[MAX_QUOTED_NAME_LEN];

	/* Nothing to do if it's a noncollatable data type */
	if (!OidIsValid(collation))
		return;

	tp = SearchSysCache1(COLLOID, ObjectIdGetDatum(collation));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "cache lookup failed for collation %u", collation);
	colltup = (Form_pg_collation) GETSTRUCT(tp);
	collname = NameStr(colltup->collname);

	/*
	 * We qualify the name always, for simplicity and to ensure the query is
	 * not search-path-dependent.
	 */
	quoteOneName(onename, get_namespace_name(colltup->collnamespace));
	appendStringInfo(buf, " COLLATE %s", onename);
	quoteOneName(onename, collname);
	appendStringInfo(buf, ".%s", onename);

	ReleaseSysCache(tp);
}