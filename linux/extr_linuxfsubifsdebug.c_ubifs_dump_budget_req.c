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
struct ubifs_budget_req {int /*<<< orphan*/  dd_growth; int /*<<< orphan*/  data_growth; int /*<<< orphan*/  idx_growth; int /*<<< orphan*/  mod_dent; int /*<<< orphan*/  new_dent; int /*<<< orphan*/  dirtied_page; int /*<<< orphan*/  new_page; int /*<<< orphan*/  dirtied_ino_d; int /*<<< orphan*/  new_ino_d; int /*<<< orphan*/  dirtied_ino; int /*<<< orphan*/  new_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_lock ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ubifs_dump_budget_req(const struct ubifs_budget_req *req)
{
	spin_lock(&dbg_lock);
	pr_err("Budgeting request: new_ino %d, dirtied_ino %d\n",
	       req->new_ino, req->dirtied_ino);
	pr_err("\tnew_ino_d   %d, dirtied_ino_d %d\n",
	       req->new_ino_d, req->dirtied_ino_d);
	pr_err("\tnew_page    %d, dirtied_page %d\n",
	       req->new_page, req->dirtied_page);
	pr_err("\tnew_dent    %d, mod_dent     %d\n",
	       req->new_dent, req->mod_dent);
	pr_err("\tidx_growth  %d\n", req->idx_growth);
	pr_err("\tdata_growth %d dd_growth     %d\n",
	       req->data_growth, req->dd_growth);
	spin_unlock(&dbg_lock);
}