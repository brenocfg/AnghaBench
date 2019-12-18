#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int valid; int /*<<< orphan*/  Num; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ NUMCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_FLAG ; 
 TYPE_1__* NUM_cache_getnew (char const*) ; 
 TYPE_1__* NUM_cache_search (char const*) ; 
 int /*<<< orphan*/  NUM_index ; 
 int /*<<< orphan*/  NUM_keywords ; 
 int /*<<< orphan*/  parse_format (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zeroize_NUM (int /*<<< orphan*/ *) ; 

__attribute__((used)) static NUMCacheEntry *
NUM_cache_fetch(const char *str)
{
	NUMCacheEntry *ent;

	if ((ent = NUM_cache_search(str)) == NULL)
	{
		/*
		 * Not in the cache, must run parser and save a new format-picture to
		 * the cache.  Do not mark the cache entry valid until parsing
		 * succeeds.
		 */
		ent = NUM_cache_getnew(str);

		zeroize_NUM(&ent->Num);

		parse_format(ent->format, str, NUM_keywords,
					 NULL, NUM_index, NUM_FLAG, &ent->Num);

		ent->valid = true;
	}
	return ent;
}