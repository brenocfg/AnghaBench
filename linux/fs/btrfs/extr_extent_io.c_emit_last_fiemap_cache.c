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
struct fiemap_extent_info {int dummy; } ;
struct fiemap_cache {int cached; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  phys; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int fiemap_fill_next_extent (struct fiemap_extent_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emit_last_fiemap_cache(struct fiemap_extent_info *fieinfo,
				  struct fiemap_cache *cache)
{
	int ret;

	if (!cache->cached)
		return 0;

	ret = fiemap_fill_next_extent(fieinfo, cache->offset, cache->phys,
				      cache->len, cache->flags);
	cache->cached = false;
	if (ret > 0)
		ret = 0;
	return ret;
}