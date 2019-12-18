#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mb_cache_entry {int /*<<< orphan*/  e_key; } ;
struct mb_cache {int dummy; } ;

/* Variables and functions */
 struct mb_cache_entry* __entry_find (struct mb_cache*,struct mb_cache_entry*,int /*<<< orphan*/ ) ; 

struct mb_cache_entry *mb_cache_entry_find_next(struct mb_cache *cache,
						struct mb_cache_entry *entry)
{
	return __entry_find(cache, entry, entry->e_key);
}