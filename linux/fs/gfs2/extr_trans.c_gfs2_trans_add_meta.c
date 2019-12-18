#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gfs2_trans {int /*<<< orphan*/  tr_num_buf_new; int /*<<< orphan*/  tr_buf; int /*<<< orphan*/  tr_flags; } ;
struct gfs2_sbd {TYPE_2__* sd_jdesc; int /*<<< orphan*/  sd_freeze_state; } ;
struct gfs2_meta_header {int /*<<< orphan*/  mh_jid; int /*<<< orphan*/  __pad0; int /*<<< orphan*/  mh_magic; } ;
struct TYPE_5__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; TYPE_1__ gl_name; } ;
struct gfs2_bufdata {int /*<<< orphan*/  bd_list; TYPE_3__* bd_bh; struct gfs2_glock* bd_gl; } ;
struct buffer_head {int /*<<< orphan*/  b_page; struct gfs2_bufdata* b_private; } ;
typedef  enum gfs2_freeze_state { ____Placeholder_gfs2_freeze_state } gfs2_freeze_state ;
struct TYPE_8__ {struct gfs2_trans* journal_info; } ;
struct TYPE_7__ {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  jd_jid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 int /*<<< orphan*/  GLF_LFLUSH ; 
 int SFS_FROZEN ; 
 int /*<<< orphan*/  TR_TOUCHED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_pinned (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,unsigned long long) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*) ; 
 struct gfs2_bufdata* gfs2_alloc_bufdata (struct gfs2_glock*,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_log_lock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_unlock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_pin (struct gfs2_sbd*,TYPE_3__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

void gfs2_trans_add_meta(struct gfs2_glock *gl, struct buffer_head *bh)
{

	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct gfs2_bufdata *bd;
	struct gfs2_meta_header *mh;
	struct gfs2_trans *tr = current->journal_info;
	enum gfs2_freeze_state state = atomic_read(&sdp->sd_freeze_state);

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
		lock_page(bh->b_page);
		if (bh->b_private == NULL)
			bd = gfs2_alloc_bufdata(gl, bh);
		else
			bd = bh->b_private;
		unlock_page(bh->b_page);
		lock_buffer(bh);
		gfs2_log_lock(sdp);
	}
	gfs2_assert(sdp, bd->bd_gl == gl);
	set_bit(TR_TOUCHED, &tr->tr_flags);
	if (!list_empty(&bd->bd_list))
		goto out_unlock;
	set_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
	set_bit(GLF_DIRTY, &bd->bd_gl->gl_flags);
	mh = (struct gfs2_meta_header *)bd->bd_bh->b_data;
	if (unlikely(mh->mh_magic != cpu_to_be32(GFS2_MAGIC))) {
		fs_err(sdp, "Attempting to add uninitialised block to "
		       "journal (inplace block=%lld)\n",
		       (unsigned long long)bd->bd_bh->b_blocknr);
		BUG();
	}
	if (unlikely(state == SFS_FROZEN)) {
		fs_info(sdp, "GFS2:adding buf while frozen\n");
		gfs2_assert_withdraw(sdp, 0);
	}
	gfs2_pin(sdp, bd->bd_bh);
	mh->__pad0 = cpu_to_be64(0);
	mh->mh_jid = cpu_to_be32(sdp->sd_jdesc->jd_jid);
	list_add(&bd->bd_list, &tr->tr_buf);
	tr->tr_num_buf_new++;
out_unlock:
	gfs2_log_unlock(sdp);
out:
	unlock_buffer(bh);
}