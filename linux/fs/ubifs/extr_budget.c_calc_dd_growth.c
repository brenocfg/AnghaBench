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
struct TYPE_2__ {int page_budget; int inode_budget; scalar_t__ dent_budget; } ;
struct ubifs_info {TYPE_1__ bi; } ;
struct ubifs_budget_req {int dirtied_ino; scalar_t__ dirtied_ino_d; scalar_t__ mod_dent; scalar_t__ dirtied_page; } ;

/* Variables and functions */

__attribute__((used)) static int calc_dd_growth(const struct ubifs_info *c,
			  const struct ubifs_budget_req *req)
{
	int dd_growth;

	dd_growth = req->dirtied_page ? c->bi.page_budget : 0;

	if (req->dirtied_ino)
		dd_growth += c->bi.inode_budget << (req->dirtied_ino - 1);
	if (req->mod_dent)
		dd_growth += c->bi.dent_budget;
	dd_growth += req->dirtied_ino_d;
	return dd_growth;
}