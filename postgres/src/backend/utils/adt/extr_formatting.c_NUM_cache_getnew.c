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
struct TYPE_4__ {int valid; scalar_t__ age; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ NUMCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_elog_output ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 TYPE_1__** NUMCache ; 
 void* NUMCounter ; 
 int NUM_CACHE_ENTRIES ; 
 scalar_t__ NUM_CACHE_SIZE ; 
 int /*<<< orphan*/  NUM_prevent_counter_overflow () ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 int n_NUMCache ; 

__attribute__((used)) static NUMCacheEntry *
NUM_cache_getnew(const char *str)
{
	NUMCacheEntry *ent;

	/* Ensure we can advance NUMCounter below */
	NUM_prevent_counter_overflow();

	/*
	 * If cache is full, remove oldest entry (or recycle first not-valid one)
	 */
	if (n_NUMCache >= NUM_CACHE_ENTRIES)
	{
		NUMCacheEntry *old = NUMCache[0];

#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "Cache is full (%d)", n_NUMCache);
#endif
		if (old->valid)
		{
			for (int i = 1; i < NUM_CACHE_ENTRIES; i++)
			{
				ent = NUMCache[i];
				if (!ent->valid)
				{
					old = ent;
					break;
				}
				if (ent->age < old->age)
					old = ent;
			}
		}
#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "OLD: \"%s\" AGE: %d", old->str, old->age);
#endif
		old->valid = false;
		StrNCpy(old->str, str, NUM_CACHE_SIZE + 1);
		old->age = (++NUMCounter);
		/* caller is expected to fill format and Num, then set valid */
		return old;
	}
	else
	{
#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "NEW (%d)", n_NUMCache);
#endif
		Assert(NUMCache[n_NUMCache] == NULL);
		NUMCache[n_NUMCache] = ent = (NUMCacheEntry *)
			MemoryContextAllocZero(TopMemoryContext, sizeof(NUMCacheEntry));
		ent->valid = false;
		StrNCpy(ent->str, str, NUM_CACHE_SIZE + 1);
		ent->age = (++NUMCounter);
		/* caller is expected to fill format and Num, then set valid */
		++n_NUMCache;
		return ent;
	}
}