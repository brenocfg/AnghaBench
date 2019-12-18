#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ shippable_extensions; TYPE_1__* server; } ;
struct TYPE_9__ {int shippable; } ;
struct TYPE_8__ {int /*<<< orphan*/  serverid; void* classid; void* objid; } ;
struct TYPE_7__ {int /*<<< orphan*/  serverid; } ;
typedef  TYPE_2__ ShippableCacheKey ;
typedef  TYPE_3__ ShippableCacheEntry ;
typedef  TYPE_4__ PgFdwRelationInfo ;
typedef  void* Oid ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  InitializeShippableCache () ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  ShippableCacheHash ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_builtin (void*) ; 
 int lookup_shippable (void*,void*,TYPE_4__*) ; 

bool
is_shippable(Oid objectId, Oid classId, PgFdwRelationInfo *fpinfo)
{
	ShippableCacheKey key;
	ShippableCacheEntry *entry;

	/* Built-in objects are presumed shippable. */
	if (is_builtin(objectId))
		return true;

	/* Otherwise, give up if user hasn't specified any shippable extensions. */
	if (fpinfo->shippable_extensions == NIL)
		return false;

	/* Initialize cache if first time through. */
	if (!ShippableCacheHash)
		InitializeShippableCache();

	/* Set up cache hash key */
	key.objid = objectId;
	key.classid = classId;
	key.serverid = fpinfo->server->serverid;

	/* See if we already cached the result. */
	entry = (ShippableCacheEntry *)
		hash_search(ShippableCacheHash,
					(void *) &key,
					HASH_FIND,
					NULL);

	if (!entry)
	{
		/* Not found in cache, so perform shippability lookup. */
		bool		shippable = lookup_shippable(objectId, classId, fpinfo);

		/*
		 * Don't create a new hash entry until *after* we have the shippable
		 * result in hand, as the underlying catalog lookups might trigger a
		 * cache invalidation.
		 */
		entry = (ShippableCacheEntry *)
			hash_search(ShippableCacheHash,
						(void *) &key,
						HASH_ENTER,
						NULL);

		entry->shippable = shippable;
	}

	return entry->shippable;
}