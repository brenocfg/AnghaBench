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
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SearchSysCacheCopy1 (int,int /*<<< orphan*/ ) ; 
 int get_object_catcache_oid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object_oid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_copytuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 

HeapTuple
get_catalog_object_by_oid(Relation catalog, AttrNumber oidcol, Oid objectId)
{
	HeapTuple	tuple;
	Oid			classId = RelationGetRelid(catalog);
	int			oidCacheId = get_object_catcache_oid(classId);

	if (oidCacheId > 0)
	{
		tuple = SearchSysCacheCopy1(oidCacheId, ObjectIdGetDatum(objectId));
		if (!HeapTupleIsValid(tuple))	/* should not happen */
			return NULL;
	}
	else
	{
		Oid			oidIndexId = get_object_oid_index(classId);
		SysScanDesc scan;
		ScanKeyData skey;

		Assert(OidIsValid(oidIndexId));

		ScanKeyInit(&skey,
					oidcol,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(objectId));

		scan = systable_beginscan(catalog, oidIndexId, true,
								  NULL, 1, &skey);
		tuple = systable_getnext(scan);
		if (!HeapTupleIsValid(tuple))
		{
			systable_endscan(scan);
			return NULL;
		}
		tuple = heap_copytuple(tuple);

		systable_endscan(scan);
	}

	return tuple;
}