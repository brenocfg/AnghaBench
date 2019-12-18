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
typedef  int int32 ;
struct TYPE_2__ {scalar_t__ collprovider; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_collation ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_collation_oid ; 
 int /*<<< orphan*/  COLLNAMEENCNSP ; 
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysCacheOid3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_encoding_supported_by_icu (int) ; 

__attribute__((used)) static Oid
lookup_collation(const char *collname, Oid collnamespace, int32 encoding)
{
	Oid			collid;
	HeapTuple	colltup;
	Form_pg_collation collform;

	/* Check for encoding-specific entry (exact match) */
	collid = GetSysCacheOid3(COLLNAMEENCNSP, Anum_pg_collation_oid,
							 PointerGetDatum(collname),
							 Int32GetDatum(encoding),
							 ObjectIdGetDatum(collnamespace));
	if (OidIsValid(collid))
		return collid;

	/*
	 * Check for any-encoding entry.  This takes a bit more work: while libc
	 * collations with collencoding = -1 do work with all encodings, ICU
	 * collations only work with certain encodings, so we have to check that
	 * aspect before deciding it's a match.
	 */
	colltup = SearchSysCache3(COLLNAMEENCNSP,
							  PointerGetDatum(collname),
							  Int32GetDatum(-1),
							  ObjectIdGetDatum(collnamespace));
	if (!HeapTupleIsValid(colltup))
		return InvalidOid;
	collform = (Form_pg_collation) GETSTRUCT(colltup);
	if (collform->collprovider == COLLPROVIDER_ICU)
	{
		if (is_encoding_supported_by_icu(encoding))
			collid = collform->oid;
		else
			collid = InvalidOid;
	}
	else
	{
		collid = collform->oid;
	}
	ReleaseSysCache(colltup);
	return collid;
}