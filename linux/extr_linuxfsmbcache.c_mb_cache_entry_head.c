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
struct mb_cache {int /*<<< orphan*/  c_bucket_bits; struct hlist_bl_head* c_hash; } ;
struct hlist_bl_head {int dummy; } ;

/* Variables and functions */
 size_t hash_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_bl_head *mb_cache_entry_head(struct mb_cache *cache,
							u32 key)
{
	return &cache->c_hash[hash_32(key, cache->c_bucket_bits)];
}