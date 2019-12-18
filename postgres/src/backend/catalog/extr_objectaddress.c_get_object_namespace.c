#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_5__ {scalar_t__ attnum_namespace; int oid_catcache_id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectPropertyType ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_object_property_data (int /*<<< orphan*/ ) ; 

Oid
get_object_namespace(const ObjectAddress *address)
{
	int			cache;
	HeapTuple	tuple;
	bool		isnull;
	Oid			oid;
	const ObjectPropertyType *property;

	/* If not owned by a namespace, just return InvalidOid. */
	property = get_object_property_data(address->classId);
	if (property->attnum_namespace == InvalidAttrNumber)
		return InvalidOid;

	/* Currently, we can only handle object types with system caches. */
	cache = property->oid_catcache_id;
	Assert(cache != -1);

	/* Fetch tuple from syscache and extract namespace attribute. */
	tuple = SearchSysCache1(cache, ObjectIdGetDatum(address->objectId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for cache %d oid %u",
			 cache, address->objectId);
	oid = DatumGetObjectId(SysCacheGetAttr(cache,
										   tuple,
										   property->attnum_namespace,
										   &isnull));
	Assert(!isnull);
	ReleaseSysCache(tuple);

	return oid;
}