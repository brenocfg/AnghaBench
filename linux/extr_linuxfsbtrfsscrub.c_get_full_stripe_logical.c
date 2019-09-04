#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_block_group_cache {int full_stripe_len; TYPE_1__ key; } ;

/* Variables and functions */
 int U32_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int div64_u64 (scalar_t__,int) ; 

__attribute__((used)) static u64 get_full_stripe_logical(struct btrfs_block_group_cache *cache,
				   u64 bytenr)
{
	u64 ret;

	/*
	 * Due to chunk item size limit, full stripe length should not be
	 * larger than U32_MAX. Just a sanity check here.
	 */
	WARN_ON_ONCE(cache->full_stripe_len >= U32_MAX);

	/*
	 * round_down() can only handle power of 2, while RAID56 full
	 * stripe length can be 64KiB * n, so we need to manually round down.
	 */
	ret = div64_u64(bytenr - cache->key.objectid, cache->full_stripe_len) *
		cache->full_stripe_len + cache->key.objectid;
	return ret;
}