#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ oprcom; scalar_t__ oprnegate; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  OperatorRelationId ; 
 int /*<<< orphan*/  OperatorUpd (scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveOperatorById(Oid operOid)
{
	Relation	relation;
	HeapTuple	tup;
	Form_pg_operator op;

	relation = table_open(OperatorRelationId, RowExclusiveLock);

	tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operOid));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for operator %u", operOid);
	op = (Form_pg_operator) GETSTRUCT(tup);

	/*
	 * Reset links from commutator and negator, if any.  In case of a
	 * self-commutator or self-negator, this means we have to re-fetch the
	 * updated tuple.  (We could optimize away updates on the tuple we're
	 * about to drop, but it doesn't seem worth convoluting the logic for.)
	 */
	if (OidIsValid(op->oprcom) || OidIsValid(op->oprnegate))
	{
		OperatorUpd(operOid, op->oprcom, op->oprnegate, true);
		if (operOid == op->oprcom || operOid == op->oprnegate)
		{
			ReleaseSysCache(tup);
			tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operOid));
			if (!HeapTupleIsValid(tup)) /* should not happen */
				elog(ERROR, "cache lookup failed for operator %u", operOid);
		}
	}

	CatalogTupleDelete(relation, &tup->t_self);

	ReleaseSysCache(tup);

	table_close(relation, RowExclusiveLock);
}