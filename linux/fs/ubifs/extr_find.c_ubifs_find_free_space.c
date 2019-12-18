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
struct ubifs_lprops {int lnum; int flags; int free; } ;
struct TYPE_4__ {scalar_t__ idx_lebs; int empty_lebs; int taken_empty_lebs; } ;
struct TYPE_3__ {scalar_t__ min_idx_lebs; } ;
struct ubifs_info {int freeable_cnt; int idx_gc_cnt; int leb_size; int /*<<< orphan*/  space_lock; TYPE_2__ lst; TYPE_1__ bi; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  LPROPS_NC ; 
 int LPROPS_TAKEN ; 
 int PTR_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  dbg_find (char*,int,...) ; 
 struct ubifs_lprops* do_find_free_space (struct ubifs_info*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct ubifs_lprops* ubifs_change_lp (struct ubifs_info*,struct ubifs_lprops const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_get_lprops (struct ubifs_info*) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_release_lprops (struct ubifs_info*) ; 

int ubifs_find_free_space(struct ubifs_info *c, int min_space, int *offs,
			  int squeeze)
{
	const struct ubifs_lprops *lprops;
	int lebs, rsvd_idx_lebs, pick_free = 0, err, lnum, flags;

	dbg_find("min_space %d", min_space);
	ubifs_get_lprops(c);

	/* Check if there are enough empty LEBs for commit */
	spin_lock(&c->space_lock);
	if (c->bi.min_idx_lebs > c->lst.idx_lebs)
		rsvd_idx_lebs = c->bi.min_idx_lebs -  c->lst.idx_lebs;
	else
		rsvd_idx_lebs = 0;
	lebs = c->lst.empty_lebs + c->freeable_cnt + c->idx_gc_cnt -
	       c->lst.taken_empty_lebs;
	if (rsvd_idx_lebs < lebs)
		/*
		 * OK to allocate an empty LEB, but we still don't want to go
		 * looking for one if there aren't any.
		 */
		if (c->lst.empty_lebs - c->lst.taken_empty_lebs > 0) {
			pick_free = 1;
			/*
			 * Because we release the space lock, we must account
			 * for this allocation here. After the LEB properties
			 * flags have been updated, we subtract one. Note, the
			 * result of this is that lprops also decreases
			 * @taken_empty_lebs in 'ubifs_change_lp()', so it is
			 * off by one for a short period of time which may
			 * introduce a small disturbance to budgeting
			 * calculations, but this is harmless because at the
			 * worst case this would make the budgeting subsystem
			 * be more pessimistic than needed.
			 *
			 * Fundamentally, this is about serialization of the
			 * budgeting and lprops subsystems. We could make the
			 * @space_lock a mutex and avoid dropping it before
			 * calling 'ubifs_change_lp()', but mutex is more
			 * heavy-weight, and we want budgeting to be as fast as
			 * possible.
			 */
			c->lst.taken_empty_lebs += 1;
		}
	spin_unlock(&c->space_lock);

	lprops = do_find_free_space(c, min_space, pick_free, squeeze);
	if (IS_ERR(lprops)) {
		err = PTR_ERR(lprops);
		goto out;
	}

	lnum = lprops->lnum;
	flags = lprops->flags | LPROPS_TAKEN;

	lprops = ubifs_change_lp(c, lprops, LPROPS_NC, LPROPS_NC, flags, 0);
	if (IS_ERR(lprops)) {
		err = PTR_ERR(lprops);
		goto out;
	}

	if (pick_free) {
		spin_lock(&c->space_lock);
		c->lst.taken_empty_lebs -= 1;
		spin_unlock(&c->space_lock);
	}

	*offs = c->leb_size - lprops->free;
	ubifs_release_lprops(c);

	if (*offs == 0) {
		/*
		 * Ensure that empty LEBs have been unmapped. They may not have
		 * been, for example, because of an unclean unmount.  Also
		 * LEBs that were freeable LEBs (free + dirty == leb_size) will
		 * not have been unmapped.
		 */
		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
	}

	dbg_find("found LEB %d, free %d", lnum, c->leb_size - *offs);
	ubifs_assert(c, *offs <= c->leb_size - min_space);
	return lnum;

out:
	if (pick_free) {
		spin_lock(&c->space_lock);
		c->lst.taken_empty_lebs -= 1;
		spin_unlock(&c->space_lock);
	}
	ubifs_release_lprops(c);
	return err;
}