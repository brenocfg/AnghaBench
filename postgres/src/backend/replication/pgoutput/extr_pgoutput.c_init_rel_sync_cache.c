#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_4__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  int /*<<< orphan*/  RelationSyncEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheRegisterRelcacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUBLICATIONRELMAP ; 
 int /*<<< orphan*/ * RelationSyncCache ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rel_sync_cache_publication_cb ; 
 int /*<<< orphan*/  rel_sync_cache_relation_cb ; 

__attribute__((used)) static void
init_rel_sync_cache(MemoryContext cachectx)
{
	HASHCTL		ctl;
	MemoryContext old_ctxt;

	if (RelationSyncCache != NULL)
		return;

	/* Make a new hash table for the cache */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(Oid);
	ctl.entrysize = sizeof(RelationSyncEntry);
	ctl.hcxt = cachectx;

	old_ctxt = MemoryContextSwitchTo(cachectx);
	RelationSyncCache = hash_create("logical replication output relation cache",
									128, &ctl,
									HASH_ELEM | HASH_CONTEXT | HASH_BLOBS);
	(void) MemoryContextSwitchTo(old_ctxt);

	Assert(RelationSyncCache != NULL);

	CacheRegisterRelcacheCallback(rel_sync_cache_relation_cb, (Datum) 0);
	CacheRegisterSyscacheCallback(PUBLICATIONRELMAP,
								  rel_sync_cache_publication_cb,
								  (Datum) 0);
}