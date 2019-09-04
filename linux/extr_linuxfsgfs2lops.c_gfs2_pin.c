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
struct gfs2_sbd {int /*<<< orphan*/  sd_log_pinned; int /*<<< orphan*/  sd_ail_lock; } ;
struct gfs2_bufdata {TYPE_1__* bd_tr; int /*<<< orphan*/  bd_ail_st_list; } ;
struct buffer_head {struct gfs2_bufdata* b_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  journal_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  tr_ail2_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_io_error_bh_wd (struct gfs2_sbd*,struct buffer_head*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_set_buffer_pinned (struct buffer_head*) ; 
 int /*<<< orphan*/  trace_gfs2_pin (struct gfs2_bufdata*,int) ; 

void gfs2_pin(struct gfs2_sbd *sdp, struct buffer_head *bh)
{
	struct gfs2_bufdata *bd;

	BUG_ON(!current->journal_info);

	clear_buffer_dirty(bh);
	if (test_set_buffer_pinned(bh))
		gfs2_assert_withdraw(sdp, 0);
	if (!buffer_uptodate(bh))
		gfs2_io_error_bh_wd(sdp, bh);
	bd = bh->b_private;
	/* If this buffer is in the AIL and it has already been written
	 * to in-place disk block, remove it from the AIL.
	 */
	spin_lock(&sdp->sd_ail_lock);
	if (bd->bd_tr)
		list_move(&bd->bd_ail_st_list, &bd->bd_tr->tr_ail2_list);
	spin_unlock(&sdp->sd_ail_lock);
	get_bh(bh);
	atomic_inc(&sdp->sd_log_pinned);
	trace_gfs2_pin(bd, 1);
}