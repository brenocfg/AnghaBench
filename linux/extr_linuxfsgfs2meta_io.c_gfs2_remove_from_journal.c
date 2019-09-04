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
struct gfs2_trans {int /*<<< orphan*/  tr_flags; int /*<<< orphan*/  tr_num_databuf_rm; int /*<<< orphan*/  tr_num_buf_rm; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_ail_lock; int /*<<< orphan*/  sd_log_pinned; } ;
struct gfs2_bufdata {scalar_t__ bd_tr; int /*<<< orphan*/  bd_list; } ;
struct buffer_head {struct gfs2_bufdata* b_private; TYPE_1__* b_page; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {struct gfs2_trans* journal_info; } ;
struct TYPE_3__ {struct address_space* mapping; } ;

/* Variables and functions */
 int REMOVE_META ; 
 int /*<<< orphan*/  TR_TOUCHED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  gfs2_bufdata_cachep ; 
 struct gfs2_sbd* gfs2_mapping2sbd (struct address_space*) ; 
 int /*<<< orphan*/  gfs2_trans_add_revoke (struct gfs2_sbd*,struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_clear_buffer_pinned (struct buffer_head*) ; 
 int /*<<< orphan*/  trace_gfs2_pin (struct gfs2_bufdata*,int /*<<< orphan*/ ) ; 

void gfs2_remove_from_journal(struct buffer_head *bh, int meta)
{
	struct address_space *mapping = bh->b_page->mapping;
	struct gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	struct gfs2_bufdata *bd = bh->b_private;
	struct gfs2_trans *tr = current->journal_info;
	int was_pinned = 0;

	if (test_clear_buffer_pinned(bh)) {
		trace_gfs2_pin(bd, 0);
		atomic_dec(&sdp->sd_log_pinned);
		list_del_init(&bd->bd_list);
		if (meta == REMOVE_META)
			tr->tr_num_buf_rm++;
		else
			tr->tr_num_databuf_rm++;
		set_bit(TR_TOUCHED, &tr->tr_flags);
		was_pinned = 1;
		brelse(bh);
	}
	if (bd) {
		spin_lock(&sdp->sd_ail_lock);
		if (bd->bd_tr) {
			gfs2_trans_add_revoke(sdp, bd);
		} else if (was_pinned) {
			bh->b_private = NULL;
			kmem_cache_free(gfs2_bufdata_cachep, bd);
		}
		spin_unlock(&sdp->sd_ail_lock);
	}
	clear_buffer_dirty(bh);
	clear_buffer_uptodate(bh);
}