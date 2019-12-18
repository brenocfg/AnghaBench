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
struct TYPE_2__ {int /*<<< orphan*/  typname; int /*<<< orphan*/  typnamespace; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getBaseType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logicalrep_write_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
logicalrep_write_typ(StringInfo out, Oid typoid)
{
	Oid			basetypoid = getBaseType(typoid);
	HeapTuple	tup;
	Form_pg_type typtup;

	pq_sendbyte(out, 'Y');		/* sending TYPE */

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(basetypoid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", basetypoid);
	typtup = (Form_pg_type) GETSTRUCT(tup);

	/* use Oid as relation identifier */
	pq_sendint32(out, typoid);

	/* send qualified type name */
	logicalrep_write_namespace(out, typtup->typnamespace);
	pq_sendstring(out, NameStr(typtup->typname));

	ReleaseSysCache(tup);
}