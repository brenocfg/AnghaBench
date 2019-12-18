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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {unsigned char* swap_map; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 unsigned char COUNT_CONTINUED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 unsigned char SWAP_HAS_CACHE ; 
 scalar_t__ SWAP_MAP_BAD ; 
 unsigned char SWAP_MAP_MAX ; 
 struct swap_info_struct* get_swap_device (int /*<<< orphan*/ ) ; 
 struct swap_cluster_info* lock_cluster_or_swap_info (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  put_swap_device (struct swap_info_struct*) ; 
 scalar_t__ swap_count (unsigned char) ; 
 scalar_t__ swap_count_continued (struct swap_info_struct*,unsigned long,unsigned char) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_cluster_or_swap_info (struct swap_info_struct*,struct swap_cluster_info*) ; 

__attribute__((used)) static int __swap_duplicate(swp_entry_t entry, unsigned char usage)
{
	struct swap_info_struct *p;
	struct swap_cluster_info *ci;
	unsigned long offset;
	unsigned char count;
	unsigned char has_cache;
	int err = -EINVAL;

	p = get_swap_device(entry);
	if (!p)
		goto out;

	offset = swp_offset(entry);
	ci = lock_cluster_or_swap_info(p, offset);

	count = p->swap_map[offset];

	/*
	 * swapin_readahead() doesn't check if a swap entry is valid, so the
	 * swap entry could be SWAP_MAP_BAD. Check here with lock held.
	 */
	if (unlikely(swap_count(count) == SWAP_MAP_BAD)) {
		err = -ENOENT;
		goto unlock_out;
	}

	has_cache = count & SWAP_HAS_CACHE;
	count &= ~SWAP_HAS_CACHE;
	err = 0;

	if (usage == SWAP_HAS_CACHE) {

		/* set SWAP_HAS_CACHE if there is no cache and entry is used */
		if (!has_cache && count)
			has_cache = SWAP_HAS_CACHE;
		else if (has_cache)		/* someone else added cache */
			err = -EEXIST;
		else				/* no users remaining */
			err = -ENOENT;

	} else if (count || has_cache) {

		if ((count & ~COUNT_CONTINUED) < SWAP_MAP_MAX)
			count += usage;
		else if ((count & ~COUNT_CONTINUED) > SWAP_MAP_MAX)
			err = -EINVAL;
		else if (swap_count_continued(p, offset, count))
			count = COUNT_CONTINUED;
		else
			err = -ENOMEM;
	} else
		err = -ENOENT;			/* unused swap entry */

	p->swap_map[offset] = count | has_cache;

unlock_out:
	unlock_cluster_or_swap_info(p, ci);
out:
	if (p)
		put_swap_device(p);
	return err;
}