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
struct TYPE_2__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  contypid; int /*<<< orphan*/  conrelid; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_oid ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_catalog_object_by_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getConstraintTypeDescription(StringInfo buffer, Oid constroid)
{
	Relation	constrRel;
	HeapTuple	constrTup;
	Form_pg_constraint constrForm;

	constrRel = table_open(ConstraintRelationId, AccessShareLock);
	constrTup = get_catalog_object_by_oid(constrRel, Anum_pg_constraint_oid,
										  constroid);
	if (!HeapTupleIsValid(constrTup))
		elog(ERROR, "cache lookup failed for constraint %u", constroid);

	constrForm = (Form_pg_constraint) GETSTRUCT(constrTup);

	if (OidIsValid(constrForm->conrelid))
		appendStringInfoString(buffer, "table constraint");
	else if (OidIsValid(constrForm->contypid))
		appendStringInfoString(buffer, "domain constraint");
	else
		elog(ERROR, "invalid constraint %u", constrForm->oid);

	table_close(constrRel, AccessShareLock);
}