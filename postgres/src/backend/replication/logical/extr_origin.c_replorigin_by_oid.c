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
struct TYPE_2__ {int /*<<< orphan*/  roname; } ;
typedef  scalar_t__ RepOriginId ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_replication_origin ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DoNotReplicateId ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidRepOriginId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPLORIGIDENT ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

bool
replorigin_by_oid(RepOriginId roident, bool missing_ok, char **roname)
{
	HeapTuple	tuple;
	Form_pg_replication_origin ric;

	Assert(OidIsValid((Oid) roident));
	Assert(roident != InvalidRepOriginId);
	Assert(roident != DoNotReplicateId);

	tuple = SearchSysCache1(REPLORIGIDENT,
							ObjectIdGetDatum((Oid) roident));

	if (HeapTupleIsValid(tuple))
	{
		ric = (Form_pg_replication_origin) GETSTRUCT(tuple);
		*roname = text_to_cstring(&ric->roname);
		ReleaseSysCache(tuple);

		return true;
	}
	else
	{
		*roname = NULL;

		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("replication origin with OID %u does not exist",
							roident)));

		return false;
	}
}