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
struct gfs2_trans {int /*<<< orphan*/  tr_databuf; int /*<<< orphan*/  tr_num_databuf_new; int /*<<< orphan*/  tr_flags; } ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_3__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; TYPE_1__ gl_name; } ;
struct gfs2_bufdata {int /*<<< orphan*/  bd_list; int /*<<< orphan*/  bd_bh; struct gfs2_glock* bd_gl; } ;
struct buffer_head {struct gfs2_bufdata* b_private; } ;
struct TYPE_4__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_DIRTY ; 
 int /*<<< orphan*/  GLF_LFLUSH ; 
 int /*<<< orphan*/  TR_TOUCHED ; 
 scalar_t__ buffer_pinned (struct buffer_head*) ; 
 TYPE_2__* current ; 
 struct gfs2_bufdata* gfs2_alloc_bufdata (struct gfs2_glock*,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_log_lock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_unlock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_pin (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void gfs2_trans_add_data(struct gfs2_glock *gl, struct buffer_head *bh)
{
	struct gfs2_trans *tr = current->journal_info;
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct gfs2_bufdata *bd;

	lock_buffer(bh);
	if (buffer_pinned(bh)) {
		set_bit(TR_TOUCHED, &tr->tr_flags);
		goto out;
	}
	gfs2_log_lock(sdp);
	bd = bh->b_private;
	if (bd == NULL) {
		gfs2_log_unlock(sdp);
		unlock_buffer(bh);
		if (bh->b_private == NULL)
			bd = gfs2_alloc_bufdata(gl, bh);
		else
			bd = bh->b_private;
		lock_buffer(bh);
		gfs2_log_lock(sdp);
	}
	gfs2_assert(sdp, bd->bd_gl == gl);
	set_bit(TR_TOUCHED, &tr->tr_flags);
	if (list_empty(&bd->bd_list)) {
		set_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
		set_bit(GLF_DIRTY, &bd->bd_gl->gl_flags);
		gfs2_pin(sdp, bd->bd_bh);
		tr->tr_num_databuf_new++;
		list_add_tail(&bd->bd_list, &tr->tr_databuf);
	}
	gfs2_log_unlock(sdp);
out:
	unlock_buffer(bh);
}