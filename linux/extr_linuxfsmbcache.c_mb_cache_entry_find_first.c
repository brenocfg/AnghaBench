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
typedef  int /*<<< orphan*/  u32 ;
struct mb_cache_entry {int dummy; } ;
struct mb_cache {int dummy; } ;

/* Variables and functions */
 struct mb_cache_entry* __entry_find (struct mb_cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct mb_cache_entry *mb_cache_entry_find_first(struct mb_cache *cache,
						 u32 key)
{
	return __entry_find(cache, NULL, key);
}