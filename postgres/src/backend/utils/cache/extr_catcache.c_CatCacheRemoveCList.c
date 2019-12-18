#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ refcount; int n_members; int /*<<< orphan*/  keys; int /*<<< orphan*/  nkeys; int /*<<< orphan*/  cache_elem; TYPE_2__** members; TYPE_1__* my_cache; } ;
struct TYPE_10__ {scalar_t__ refcount; scalar_t__ dead; TYPE_3__* c_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  cc_keyno; int /*<<< orphan*/  cc_tupdesc; } ;
typedef  TYPE_1__ CatCache ;
typedef  TYPE_2__ CatCTup ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CatCacheFreeKeys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatCacheRemoveCTup (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

__attribute__((used)) static void
CatCacheRemoveCList(CatCache *cache, CatCList *cl)
{
	int			i;

	Assert(cl->refcount == 0);
	Assert(cl->my_cache == cache);

	/* delink from member tuples */
	for (i = cl->n_members; --i >= 0;)
	{
		CatCTup    *ct = cl->members[i];

		Assert(ct->c_list == cl);
		ct->c_list = NULL;
		/* if the member is dead and now has no references, remove it */
		if (
#ifndef CATCACHE_FORCE_RELEASE
			ct->dead &&
#endif
			ct->refcount == 0)
			CatCacheRemoveCTup(cache, ct);
	}

	/* delink from linked list */
	dlist_delete(&cl->cache_elem);

	/* free associated column data */
	CatCacheFreeKeys(cache->cc_tupdesc, cl->nkeys,
					 cache->cc_keyno, cl->keys);

	pfree(cl);
}