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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct fiemap_extent_info {int dummy; } ;
struct fiemap_cache {int cached; scalar_t__ offset; scalar_t__ len; scalar_t__ phys; int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIEMAP_EXTENT_LAST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fiemap_fill_next_extent (struct fiemap_extent_info*,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int emit_fiemap_extent(struct fiemap_extent_info *fieinfo,
				struct fiemap_cache *cache,
				u64 offset, u64 phys, u64 len, u32 flags)
{
	int ret = 0;

	if (!cache->cached)
		goto assign;

	/*
	 * Sanity check, extent_fiemap() should have ensured that new
	 * fiemap extent won't overlap with cached one.
	 * Not recoverable.
	 *
	 * NOTE: Physical address can overlap, due to compression
	 */
	if (cache->offset + cache->len > offset) {
		WARN_ON(1);
		return -EINVAL;
	}

	/*
	 * Only merges fiemap extents if
	 * 1) Their logical addresses are continuous
	 *
	 * 2) Their physical addresses are continuous
	 *    So truly compressed (physical size smaller than logical size)
	 *    extents won't get merged with each other
	 *
	 * 3) Share same flags except FIEMAP_EXTENT_LAST
	 *    So regular extent won't get merged with prealloc extent
	 */
	if (cache->offset + cache->len  == offset &&
	    cache->phys + cache->len == phys  &&
	    (cache->flags & ~FIEMAP_EXTENT_LAST) ==
			(flags & ~FIEMAP_EXTENT_LAST)) {
		cache->len += len;
		cache->flags |= flags;
		goto try_submit_last;
	}

	/* Not mergeable, need to submit cached one */
	ret = fiemap_fill_next_extent(fieinfo, cache->offset, cache->phys,
				      cache->len, cache->flags);
	cache->cached = false;
	if (ret)
		return ret;
assign:
	cache->cached = true;
	cache->offset = offset;
	cache->phys = phys;
	cache->len = len;
	cache->flags = flags;
try_submit_last:
	if (cache->flags & FIEMAP_EXTENT_LAST) {
		ret = fiemap_fill_next_extent(fieinfo, cache->offset,
				cache->phys, cache->len, cache->flags);
		cache->cached = false;
	}
	return ret;
}