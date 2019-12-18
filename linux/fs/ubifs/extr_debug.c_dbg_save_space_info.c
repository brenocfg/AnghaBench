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
struct ubifs_lp_stats {int dummy; } ;
struct ubifs_info {int freeable_cnt; int /*<<< orphan*/  space_lock; int /*<<< orphan*/  idx_gc_cnt; int /*<<< orphan*/  bi; int /*<<< orphan*/  lst; struct ubifs_debug_info* dbg; } ;
struct ubifs_debug_info {int /*<<< orphan*/  saved_free; int /*<<< orphan*/  saved_idx_gc_cnt; int /*<<< orphan*/  saved_bi; int /*<<< orphan*/  saved_lst; } ;
struct ubifs_budg_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_get_free_space_nolock (struct ubifs_info*) ; 

void dbg_save_space_info(struct ubifs_info *c)
{
	struct ubifs_debug_info *d = c->dbg;
	int freeable_cnt;

	spin_lock(&c->space_lock);
	memcpy(&d->saved_lst, &c->lst, sizeof(struct ubifs_lp_stats));
	memcpy(&d->saved_bi, &c->bi, sizeof(struct ubifs_budg_info));
	d->saved_idx_gc_cnt = c->idx_gc_cnt;

	/*
	 * We use a dirty hack here and zero out @c->freeable_cnt, because it
	 * affects the free space calculations, and UBIFS might not know about
	 * all freeable eraseblocks. Indeed, we know about freeable eraseblocks
	 * only when we read their lprops, and we do this only lazily, upon the
	 * need. So at any given point of time @c->freeable_cnt might be not
	 * exactly accurate.
	 *
	 * Just one example about the issue we hit when we did not zero
	 * @c->freeable_cnt.
	 * 1. The file-system is mounted R/O, c->freeable_cnt is %0. We save the
	 *    amount of free space in @d->saved_free
	 * 2. We re-mount R/W, which makes UBIFS to read the "lsave"
	 *    information from flash, where we cache LEBs from various
	 *    categories ('ubifs_remount_fs()' -> 'ubifs_lpt_init()'
	 *    -> 'lpt_init_wr()' -> 'read_lsave()' -> 'ubifs_lpt_lookup()'
	 *    -> 'ubifs_get_pnode()' -> 'update_cats()'
	 *    -> 'ubifs_add_to_cat()').
	 * 3. Lsave contains a freeable eraseblock, and @c->freeable_cnt
	 *    becomes %1.
	 * 4. We calculate the amount of free space when the re-mount is
	 *    finished in 'dbg_check_space_info()' and it does not match
	 *    @d->saved_free.
	 */
	freeable_cnt = c->freeable_cnt;
	c->freeable_cnt = 0;
	d->saved_free = ubifs_get_free_space_nolock(c);
	c->freeable_cnt = freeable_cnt;
	spin_unlock(&c->space_lock);
}