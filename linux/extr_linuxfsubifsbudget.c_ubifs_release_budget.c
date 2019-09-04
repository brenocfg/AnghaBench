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
struct TYPE_2__ {int idx_growth; int data_growth; int dd_growth; scalar_t__ min_idx_lebs; int /*<<< orphan*/  uncommitted_idx; scalar_t__ nospace_rp; scalar_t__ nospace; } ;
struct ubifs_info {scalar_t__ main_lebs; int /*<<< orphan*/  space_lock; TYPE_1__ bi; } ;
struct ubifs_budget_req {int new_page; int dirtied_page; int new_dent; int mod_dent; int new_ino; int new_ino_d; int dirtied_ino; int dirtied_ino_d; scalar_t__ idx_growth; scalar_t__ data_growth; scalar_t__ dd_growth; scalar_t__ recalculate; } ;

/* Variables and functions */
 int UBIFS_MAX_INO_DATA ; 
 scalar_t__ calc_data_growth (struct ubifs_info*,struct ubifs_budget_req*) ; 
 scalar_t__ calc_dd_growth (struct ubifs_info*,struct ubifs_budget_req*) ; 
 scalar_t__ calc_idx_growth (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ ubifs_calc_min_idx_lebs (struct ubifs_info*) ; 

void ubifs_release_budget(struct ubifs_info *c, struct ubifs_budget_req *req)
{
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
	if (!req->recalculate) {
		ubifs_assert(c, req->idx_growth >= 0);
		ubifs_assert(c, req->data_growth >= 0);
		ubifs_assert(c, req->dd_growth >= 0);
	}

	if (req->recalculate) {
		req->data_growth = calc_data_growth(c, req);
		req->dd_growth = calc_dd_growth(c, req);
		req->idx_growth = calc_idx_growth(c, req);
	}

	if (!req->data_growth && !req->dd_growth)
		return;

	c->bi.nospace = c->bi.nospace_rp = 0;
	smp_wmb();

	spin_lock(&c->space_lock);
	c->bi.idx_growth -= req->idx_growth;
	c->bi.uncommitted_idx += req->idx_growth;
	c->bi.data_growth -= req->data_growth;
	c->bi.dd_growth -= req->dd_growth;
	c->bi.min_idx_lebs = ubifs_calc_min_idx_lebs(c);

	ubifs_assert(c, c->bi.idx_growth >= 0);
	ubifs_assert(c, c->bi.data_growth >= 0);
	ubifs_assert(c, c->bi.dd_growth >= 0);
	ubifs_assert(c, c->bi.min_idx_lebs < c->main_lebs);
	ubifs_assert(c, !(c->bi.idx_growth & 7));
	ubifs_assert(c, !(c->bi.data_growth & 7));
	ubifs_assert(c, !(c->bi.dd_growth & 7));
	spin_unlock(&c->space_lock);
}