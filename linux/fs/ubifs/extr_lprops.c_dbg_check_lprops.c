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
typedef  int /*<<< orphan*/  ubifs_lpt_scan_callback ;
struct ubifs_lp_stats {scalar_t__ empty_lebs; scalar_t__ idx_lebs; scalar_t__ total_free; scalar_t__ total_dirty; scalar_t__ total_used; scalar_t__ total_dead; scalar_t__ total_dark; } ;
struct TYPE_4__ {scalar_t__ empty_lebs; scalar_t__ idx_lebs; scalar_t__ total_free; scalar_t__ total_dirty; scalar_t__ total_used; scalar_t__ total_dead; scalar_t__ total_dark; } ;
struct ubifs_info {int jhead_cnt; TYPE_2__ lst; scalar_t__ leb_cnt; int /*<<< orphan*/  main_first; TYPE_1__* jheads; } ;
struct TYPE_3__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int dbg_check_cats (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_is_chk_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  memset (struct ubifs_lp_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scan_check_cb ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,...) ; 
 int ubifs_lpt_scan_nolock (struct ubifs_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct ubifs_lp_stats*) ; 
 int ubifs_wbuf_sync (int /*<<< orphan*/ *) ; 

int dbg_check_lprops(struct ubifs_info *c)
{
	int i, err;
	struct ubifs_lp_stats lst;

	if (!dbg_is_chk_lprops(c))
		return 0;

	/*
	 * As we are going to scan the media, the write buffers have to be
	 * synchronized.
	 */
	for (i = 0; i < c->jhead_cnt; i++) {
		err = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (err)
			return err;
	}

	memset(&lst, 0, sizeof(struct ubifs_lp_stats));
	err = ubifs_lpt_scan_nolock(c, c->main_first, c->leb_cnt - 1,
				    (ubifs_lpt_scan_callback)scan_check_cb,
				    &lst);
	if (err && err != -ENOSPC)
		goto out;

	if (lst.empty_lebs != c->lst.empty_lebs ||
	    lst.idx_lebs != c->lst.idx_lebs ||
	    lst.total_free != c->lst.total_free ||
	    lst.total_dirty != c->lst.total_dirty ||
	    lst.total_used != c->lst.total_used) {
		ubifs_err(c, "bad overall accounting");
		ubifs_err(c, "calculated: empty_lebs %d, idx_lebs %d, total_free %lld, total_dirty %lld, total_used %lld",
			  lst.empty_lebs, lst.idx_lebs, lst.total_free,
			  lst.total_dirty, lst.total_used);
		ubifs_err(c, "read from lprops: empty_lebs %d, idx_lebs %d, total_free %lld, total_dirty %lld, total_used %lld",
			  c->lst.empty_lebs, c->lst.idx_lebs, c->lst.total_free,
			  c->lst.total_dirty, c->lst.total_used);
		err = -EINVAL;
		goto out;
	}

	if (lst.total_dead != c->lst.total_dead ||
	    lst.total_dark != c->lst.total_dark) {
		ubifs_err(c, "bad dead/dark space accounting");
		ubifs_err(c, "calculated: total_dead %lld, total_dark %lld",
			  lst.total_dead, lst.total_dark);
		ubifs_err(c, "read from lprops: total_dead %lld, total_dark %lld",
			  c->lst.total_dead, c->lst.total_dark);
		err = -EINVAL;
		goto out;
	}

	err = dbg_check_cats(c);
out:
	return err;
}