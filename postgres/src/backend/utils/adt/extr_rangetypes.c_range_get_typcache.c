#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type_id; int /*<<< orphan*/ * rngelemtype; } ;
typedef  TYPE_2__ TypeCacheEntry ;
struct TYPE_9__ {TYPE_1__* flinfo; } ;
struct TYPE_7__ {void* fn_extra; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  TYPECACHE_RANGE_INFO ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_2__* lookup_type_cache (scalar_t__,int /*<<< orphan*/ ) ; 

TypeCacheEntry *
range_get_typcache(FunctionCallInfo fcinfo, Oid rngtypid)
{
	TypeCacheEntry *typcache = (TypeCacheEntry *) fcinfo->flinfo->fn_extra;

	if (typcache == NULL ||
		typcache->type_id != rngtypid)
	{
		typcache = lookup_type_cache(rngtypid, TYPECACHE_RANGE_INFO);
		if (typcache->rngelemtype == NULL)
			elog(ERROR, "type %u is not a range type", rngtypid);
		fcinfo->flinfo->fn_extra = (void *) typcache;
	}

	return typcache;
}