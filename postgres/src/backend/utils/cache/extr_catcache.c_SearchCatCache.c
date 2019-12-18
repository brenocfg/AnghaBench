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
struct TYPE_4__ {int /*<<< orphan*/  cc_nkeys; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ CatCache ;

/* Variables and functions */
 int /*<<< orphan*/  SearchCatCacheInternal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HeapTuple
SearchCatCache(CatCache *cache,
			   Datum v1,
			   Datum v2,
			   Datum v3,
			   Datum v4)
{
	return SearchCatCacheInternal(cache, cache->cc_nkeys, v1, v2, v3, v4);
}