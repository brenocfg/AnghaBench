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
struct TYPE_2__ {int idx_growth; int data_growth; int dd_growth; int nospace; int nospace_rp; } ;
struct ubifs_info {scalar_t__ rp_size; TYPE_1__ bi; int /*<<< orphan*/  space_lock; } ;
struct ubifs_budget_req {int new_page; int dirtied_page; int new_dent; int mod_dent; int new_ino; int new_ino_d; int dirtied_ino; int dirtied_ino_d; int idx_growth; int data_growth; int dd_growth; scalar_t__ fast; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSPC ; 
 int UBIFS_MAX_INO_DATA ; 
 int calc_data_growth (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int calc_dd_growth (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int calc_idx_growth (struct ubifs_info*,struct ubifs_budget_req*) ; 
 scalar_t__ can_use_rp (struct ubifs_info*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dbg_budg (char*) ; 
 int do_budget_space (struct ubifs_info*) ; 
 scalar_t__ likely (int) ; 
 int make_free_space (struct ubifs_info*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

int ubifs_budget_space(struct ubifs_info *c, struct ubifs_budget_req *req)
{
	int err, idx_growth, data_growth, dd_growth, retried = 0;

	ubifs_assert(c, req->new_page <= 1);
	ubifs_assert(c, req->dirtied_page <= 1);
	ubifs_assert(c, req->new_dent <= 1);
	ubifs_assert(c, req->mod_dent <= 1);
	ubifs_assert(c, req->new_ino <= 1);
	ubifs_assert(c, req->new_ino_d <= UBIFS_MAX_INO_DATA);
	ubifs_assert(c, req->dirtied_ino <= 4);
	ubifs_assert(c, req->dirtied_ino_d <= UBIFS_MAX_INO_DATA * 4);
	ubifs_assert(c, !(req->new_ino_d & 7));
	ubifs_assert(c, !(req->dirtied_ino_d & 7));

	data_growth = calc_data_growth(c, req);
	dd_growth = calc_dd_growth(c, req);
	if (!data_growth && !dd_growth)
		return 0;
	idx_growth = calc_idx_growth(c, req);

again:
	spin_lock(&c->space_lock);
	ubifs_assert(c, c->bi.idx_growth >= 0);
	ubifs_assert(c, c->bi.data_growth >= 0);
	ubifs_assert(c, c->bi.dd_growth >= 0);

	if (unlikely(c->bi.nospace) && (c->bi.nospace_rp || !can_use_rp(c))) {
		dbg_budg("no space");
		spin_unlock(&c->space_lock);
		return -ENOSPC;
	}

	c->bi.idx_growth += idx_growth;
	c->bi.data_growth += data_growth;
	c->bi.dd_growth += dd_growth;

	err = do_budget_space(c);
	if (likely(!err)) {
		req->idx_growth = idx_growth;
		req->data_growth = data_growth;
		req->dd_growth = dd_growth;
		spin_unlock(&c->space_lock);
		return 0;
	}

	/* Restore the old values */
	c->bi.idx_growth -= idx_growth;
	c->bi.data_growth -= data_growth;
	c->bi.dd_growth -= dd_growth;
	spin_unlock(&c->space_lock);

	if (req->fast) {
		dbg_budg("no space for fast budgeting");
		return err;
	}

	err = make_free_space(c);
	cond_resched();
	if (err == -EAGAIN) {
		dbg_budg("try again");
		goto again;
	} else if (err == -ENOSPC) {
		if (!retried) {
			retried = 1;
			dbg_budg("-ENOSPC, but anyway try once again");
			goto again;
		}
		dbg_budg("FS is full, -ENOSPC");
		c->bi.nospace = 1;
		if (can_use_rp(c) || c->rp_size == 0)
			c->bi.nospace_rp = 1;
		smp_wmb();
	} else
		ubifs_err(c, "cannot budget space, error %d", err);
	return err;
}