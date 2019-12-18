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
struct TYPE_2__ {scalar_t__ ev_class; scalar_t__ oid; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_rewrite ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  RULERELNAME ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (scalar_t__) ; 

Oid
get_rewrite_oid(Oid relid, const char *rulename, bool missing_ok)
{
	HeapTuple	tuple;
	Form_pg_rewrite ruleform;
	Oid			ruleoid;

	/* Find the rule's pg_rewrite tuple, get its OID */
	tuple = SearchSysCache2(RULERELNAME,
							ObjectIdGetDatum(relid),
							PointerGetDatum(rulename));
	if (!HeapTupleIsValid(tuple))
	{
		if (missing_ok)
			return InvalidOid;
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("rule \"%s\" for relation \"%s\" does not exist",
						rulename, get_rel_name(relid))));
	}
	ruleform = (Form_pg_rewrite) GETSTRUCT(tuple);
	Assert(relid == ruleform->ev_class);
	ruleoid = ruleform->oid;
	ReleaseSysCache(tuple);
	return ruleoid;
}