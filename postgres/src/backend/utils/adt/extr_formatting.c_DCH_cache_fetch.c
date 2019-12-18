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
struct TYPE_5__ {int valid; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ DCHCacheEntry ;

/* Variables and functions */
 int DCH_FLAG ; 
 TYPE_1__* DCH_cache_getnew (char const*,int) ; 
 TYPE_1__* DCH_cache_search (char const*,int) ; 
 int /*<<< orphan*/  DCH_index ; 
 int /*<<< orphan*/  DCH_keywords ; 
 int /*<<< orphan*/  DCH_suff ; 
 int STD_FLAG ; 
 int /*<<< orphan*/  parse_format (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DCHCacheEntry *
DCH_cache_fetch(const char *str, bool std)
{
	DCHCacheEntry *ent;

	if ((ent = DCH_cache_search(str, std)) == NULL)
	{
		/*
		 * Not in the cache, must run parser and save a new format-picture to
		 * the cache.  Do not mark the cache entry valid until parsing
		 * succeeds.
		 */
		ent = DCH_cache_getnew(str, std);

		parse_format(ent->format, str, DCH_keywords, DCH_suff, DCH_index,
					 DCH_FLAG | (std ? STD_FLAG : 0), NULL);

		ent->valid = true;
	}
	return ent;
}