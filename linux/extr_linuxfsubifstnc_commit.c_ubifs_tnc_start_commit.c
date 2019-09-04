#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_zbranch {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx_lebs; } ;
struct TYPE_3__ {scalar_t__ min_idx_lebs; scalar_t__ uncommitted_idx; int /*<<< orphan*/  old_idx_sz; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/  calc_idx_sz; TYPE_2__ lst; int /*<<< orphan*/  space_lock; TYPE_1__ bi; int /*<<< orphan*/  zroot; int /*<<< orphan*/  dirty_zn_cnt; } ;

/* Variables and functions */
 int ENOSPC ; 
 int alloc_idx_lebs (struct ubifs_info*,int) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int dbg_check_tnc (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  dbg_cmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_old_idx (struct ubifs_info*) ; 
 int /*<<< orphan*/  free_idx_lebs (struct ubifs_info*) ; 
 int free_unused_idx_lebs (struct ubifs_info*) ; 
 int get_znodes_to_commit (struct ubifs_info*) ; 
 int layout_commit (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  memcpy (struct ubifs_zbranch*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ ubifs_calc_min_idx_lebs (struct ubifs_info*) ; 
 int ubifs_save_dirty_idx_lnums (struct ubifs_info*) ; 

int ubifs_tnc_start_commit(struct ubifs_info *c, struct ubifs_zbranch *zroot)
{
	int err = 0, cnt;

	mutex_lock(&c->tnc_mutex);
	err = dbg_check_tnc(c, 1);
	if (err)
		goto out;
	cnt = get_znodes_to_commit(c);
	if (cnt != 0) {
		int no_space = 0;

		err = alloc_idx_lebs(c, cnt);
		if (err == -ENOSPC)
			no_space = 1;
		else if (err)
			goto out_free;
		err = layout_commit(c, no_space, cnt);
		if (err)
			goto out_free;
		ubifs_assert(c, atomic_long_read(&c->dirty_zn_cnt) == 0);
		err = free_unused_idx_lebs(c);
		if (err)
			goto out;
	}
	destroy_old_idx(c);
	memcpy(zroot, &c->zroot, sizeof(struct ubifs_zbranch));

	err = ubifs_save_dirty_idx_lnums(c);
	if (err)
		goto out;

	spin_lock(&c->space_lock);
	/*
	 * Although we have not finished committing yet, update size of the
	 * committed index ('c->bi.old_idx_sz') and zero out the index growth
	 * budget. It is OK to do this now, because we've reserved all the
	 * space which is needed to commit the index, and it is save for the
	 * budgeting subsystem to assume the index is already committed,
	 * even though it is not.
	 */
	ubifs_assert(c, c->bi.min_idx_lebs == ubifs_calc_min_idx_lebs(c));
	c->bi.old_idx_sz = c->calc_idx_sz;
	c->bi.uncommitted_idx = 0;
	c->bi.min_idx_lebs = ubifs_calc_min_idx_lebs(c);
	spin_unlock(&c->space_lock);
	mutex_unlock(&c->tnc_mutex);

	dbg_cmt("number of index LEBs %d", c->lst.idx_lebs);
	dbg_cmt("size of index %llu", c->calc_idx_sz);
	return err;

out_free:
	free_idx_lebs(c);
out:
	mutex_unlock(&c->tnc_mutex);
	return err;
}