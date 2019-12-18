#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ch_ntup; } ;
struct TYPE_9__ {scalar_t__ refcount; int dead; int /*<<< orphan*/  keys; scalar_t__ negative; int /*<<< orphan*/  cache_elem; scalar_t__ c_list; TYPE_1__* my_cache; } ;
struct TYPE_8__ {int /*<<< orphan*/  cc_ntup; int /*<<< orphan*/  cc_keyno; int /*<<< orphan*/  cc_nkeys; int /*<<< orphan*/  cc_tupdesc; } ;
typedef  TYPE_1__ CatCache ;
typedef  TYPE_2__ CatCTup ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_7__* CacheHdr ; 
 int /*<<< orphan*/  CatCacheFreeKeys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatCacheRemoveCList (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
CatCacheRemoveCTup(CatCache *cache, CatCTup *ct)
{
	Assert(ct->refcount == 0);
	Assert(ct->my_cache == cache);

	if (ct->c_list)
	{
		/*
		 * The cleanest way to handle this is to call CatCacheRemoveCList,
		 * which will recurse back to me, and the recursive call will do the
		 * work.  Set the "dead" flag to make sure it does recurse.
		 */
		ct->dead = true;
		CatCacheRemoveCList(cache, ct->c_list);
		return;					/* nothing left to do */
	}

	/* delink from linked list */
	dlist_delete(&ct->cache_elem);

	/*
	 * Free keys when we're dealing with a negative entry, normal entries just
	 * point into tuple, allocated together with the CatCTup.
	 */
	if (ct->negative)
		CatCacheFreeKeys(cache->cc_tupdesc, cache->cc_nkeys,
						 cache->cc_keyno, ct->keys);

	pfree(ct);

	--cache->cc_ntup;
	--CacheHdr->ch_ntup;
}