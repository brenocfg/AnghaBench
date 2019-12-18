#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ id; int /*<<< orphan*/  cc_reloid; int /*<<< orphan*/  cc_indexoid; int /*<<< orphan*/ * cc_tupdesc; } ;
struct TYPE_9__ {TYPE_1__* rd_index; } ;
struct TYPE_8__ {scalar_t__ indimmediate; scalar_t__ indisunique; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ CatCache ;

/* Variables and functions */
 scalar_t__ AMNAME ; 
 scalar_t__ AMOID ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CatalogCacheInitializeCache (TYPE_3__*) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
InitCatCachePhase2(CatCache *cache, bool touch_index)
{
	if (cache->cc_tupdesc == NULL)
		CatalogCacheInitializeCache(cache);

	if (touch_index &&
		cache->id != AMOID &&
		cache->id != AMNAME)
	{
		Relation	idesc;

		/*
		 * We must lock the underlying catalog before opening the index to
		 * avoid deadlock, since index_open could possibly result in reading
		 * this same catalog, and if anyone else is exclusive-locking this
		 * catalog and index they'll be doing it in that order.
		 */
		LockRelationOid(cache->cc_reloid, AccessShareLock);
		idesc = index_open(cache->cc_indexoid, AccessShareLock);

		/*
		 * While we've got the index open, let's check that it's unique (and
		 * not just deferrable-unique, thank you very much).  This is just to
		 * catch thinkos in definitions of new catcaches, so we don't worry
		 * about the pg_am indexes not getting tested.
		 */
		Assert(idesc->rd_index->indisunique &&
			   idesc->rd_index->indimmediate);

		index_close(idesc, AccessShareLock);
		UnlockRelationOid(cache->cc_reloid, AccessShareLock);
	}
}