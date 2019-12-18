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
struct ubifs_lpt_lprops {int dummy; } ;
struct ubifs_info {int lpt_lebs; int lpt_drty_flgs; int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  ltab; int /*<<< orphan*/  ltab_cmt; TYPE_1__* mst_node; scalar_t__ big_lpt; int /*<<< orphan*/  dirty_pn_cnt; scalar_t__ check_lpt_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash_lpt; } ;

/* Variables and functions */
 int LSAVE_DIRTY ; 
 int LTAB_DIRTY ; 
 int dbg_check_ltab (struct ubifs_info*) ; 
 int dbg_chk_lpt_free_spc (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_cmt (char*) ; 
 int /*<<< orphan*/  dbg_lp (char*) ; 
 int get_cnodes_to_commit (struct ubifs_info*) ; 
 int layout_cnodes (struct ubifs_info*) ; 
 int lpt_gc (struct ubifs_info*) ; 
 int /*<<< orphan*/  lpt_tgc_start (struct ubifs_info*) ; 
 int make_tree_dirty (struct ubifs_info*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ need_write_all (struct ubifs_info*) ; 
 int /*<<< orphan*/  populate_lsave (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_lpt_calc_hash (struct ubifs_info*,int /*<<< orphan*/ ) ; 

int ubifs_lpt_start_commit(struct ubifs_info *c)
{
	int err, cnt;

	dbg_lp("");

	mutex_lock(&c->lp_mutex);
	err = dbg_chk_lpt_free_spc(c);
	if (err)
		goto out;
	err = dbg_check_ltab(c);
	if (err)
		goto out;

	if (c->check_lpt_free) {
		/*
		 * We ensure there is enough free space in
		 * ubifs_lpt_post_commit() by marking nodes dirty. That
		 * information is lost when we unmount, so we also need
		 * to check free space once after mounting also.
		 */
		c->check_lpt_free = 0;
		while (need_write_all(c)) {
			mutex_unlock(&c->lp_mutex);
			err = lpt_gc(c);
			if (err)
				return err;
			mutex_lock(&c->lp_mutex);
		}
	}

	lpt_tgc_start(c);

	if (!c->dirty_pn_cnt) {
		dbg_cmt("no cnodes to commit");
		err = 0;
		goto out;
	}

	if (!c->big_lpt && need_write_all(c)) {
		/* If needed, write everything */
		err = make_tree_dirty(c);
		if (err)
			goto out;
		lpt_tgc_start(c);
	}

	if (c->big_lpt)
		populate_lsave(c);

	cnt = get_cnodes_to_commit(c);
	ubifs_assert(c, cnt != 0);

	err = layout_cnodes(c);
	if (err)
		goto out;

	err = ubifs_lpt_calc_hash(c, c->mst_node->hash_lpt);
	if (err)
		goto out;

	/* Copy the LPT's own lprops for end commit to write */
	memcpy(c->ltab_cmt, c->ltab,
	       sizeof(struct ubifs_lpt_lprops) * c->lpt_lebs);
	c->lpt_drty_flgs &= ~(LTAB_DIRTY | LSAVE_DIRTY);

out:
	mutex_unlock(&c->lp_mutex);
	return err;
}