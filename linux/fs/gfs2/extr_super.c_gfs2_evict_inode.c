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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct address_space {int dummy; } ;
struct inode {struct address_space i_data; int /*<<< orphan*/  i_mode; scalar_t__ i_nlink; struct super_block* i_sb; } ;
struct gfs2_sbd {TYPE_1__* sd_jdesc; } ;
struct gfs2_holder {int gh_flags; struct gfs2_glock* gh_gl; int /*<<< orphan*/  gh_iflags; } ;
struct gfs2_inode {int i_diskflags; struct gfs2_holder i_iopen_gh; struct gfs2_glock* i_gl; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_res; scalar_t__ i_eattr; int /*<<< orphan*/  i_no_addr; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  jd_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EROFS ; 
 int /*<<< orphan*/  GFS2_BLKST_UNLINKED ; 
 int GFS2_DIF_EXHASH ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int GFS2_LFC_EVICT_INODE ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 int /*<<< orphan*/  GIF_ALLOC_FAILED ; 
 int /*<<< orphan*/  GIF_FREE_VFS_INODE ; 
 int /*<<< orphan*/  GIF_GLOP_PENDING ; 
 int /*<<< orphan*/  GIF_INVALID ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 int GLR_TRYFAILED ; 
 int GL_NOCACHE ; 
 int /*<<< orphan*/  GL_SKIP ; 
 int /*<<< orphan*/  HIF_HOLDER ; 
 int LM_FLAG_TRY_1CB ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int PF_MEMALLOC ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (struct address_space*) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_ail_flush (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int gfs2_check_blk_type (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_dinode_dealloc (struct gfs2_inode*) ; 
 int gfs2_dir_exhash_dealloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dir_hash_inval (struct gfs2_inode*) ; 
 int gfs2_ea_dealloc (struct gfs2_inode*) ; 
 int gfs2_file_dealloc (struct gfs2_inode*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_add_to_lru (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_wait (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_hold (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_is_locked_by_me (struct gfs2_glock*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_put_eventually (struct gfs2_glock*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_mark_uninitialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_reinit (int /*<<< orphan*/ ,int,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int gfs2_inode_refresh (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_is_stuffed (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,struct gfs2_glock*,int) ; 
 int /*<<< orphan*/  gfs2_ordered_del_inode (struct gfs2_inode*) ; 
 scalar_t__ gfs2_rs_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_rs_deltree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_rsqa_delete (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  glock_clear_object (struct gfs2_glock*,struct gfs2_inode*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (struct address_space*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_bit_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

__attribute__((used)) static void gfs2_evict_inode(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder gh;
	struct address_space *metamapping;
	int error;

	if (test_bit(GIF_FREE_VFS_INODE, &ip->i_flags)) {
		clear_inode(inode);
		return;
	}

	if (inode->i_nlink || sb_rdonly(sb))
		goto out;

	if (test_bit(GIF_ALLOC_FAILED, &ip->i_flags)) {
		BUG_ON(!gfs2_glock_is_locked_by_me(ip->i_gl));
		gfs2_holder_mark_uninitialized(&gh);
		goto alloc_failed;
	}

	/* Deletes should never happen under memory pressure anymore.  */
	if (WARN_ON_ONCE(current->flags & PF_MEMALLOC))
		goto out;

	/* Must not read inode block until block type has been verified */
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, GL_SKIP, &gh);
	if (unlikely(error)) {
		glock_clear_object(ip->i_iopen_gh.gh_gl, ip);
		ip->i_iopen_gh.gh_flags |= GL_NOCACHE;
		gfs2_glock_dq_uninit(&ip->i_iopen_gh);
		goto out;
	}

	error = gfs2_check_blk_type(sdp, ip->i_no_addr, GFS2_BLKST_UNLINKED);
	if (error)
		goto out_truncate;

	if (test_bit(GIF_INVALID, &ip->i_flags)) {
		error = gfs2_inode_refresh(ip);
		if (error)
			goto out_truncate;
	}

	/*
	 * The inode may have been recreated in the meantime.
	 */
	if (inode->i_nlink)
		goto out_truncate;

alloc_failed:
	if (gfs2_holder_initialized(&ip->i_iopen_gh) &&
	    test_bit(HIF_HOLDER, &ip->i_iopen_gh.gh_iflags)) {
		ip->i_iopen_gh.gh_flags |= GL_NOCACHE;
		gfs2_glock_dq_wait(&ip->i_iopen_gh);
		gfs2_holder_reinit(LM_ST_EXCLUSIVE, LM_FLAG_TRY_1CB | GL_NOCACHE,
				   &ip->i_iopen_gh);
		error = gfs2_glock_nq(&ip->i_iopen_gh);
		if (error)
			goto out_truncate;
	}

	if (S_ISDIR(inode->i_mode) &&
	    (ip->i_diskflags & GFS2_DIF_EXHASH)) {
		error = gfs2_dir_exhash_dealloc(ip);
		if (error)
			goto out_unlock;
	}

	if (ip->i_eattr) {
		error = gfs2_ea_dealloc(ip);
		if (error)
			goto out_unlock;
	}

	if (!gfs2_is_stuffed(ip)) {
		error = gfs2_file_dealloc(ip);
		if (error)
			goto out_unlock;
	}

	/* We're about to clear the bitmap for the dinode, but as soon as we
	   do, gfs2_create_inode can create another inode at the same block
	   location and try to set gl_object again. We clear gl_object here so
	   that subsequent inode creates don't see an old gl_object. */
	glock_clear_object(ip->i_gl, ip);
	error = gfs2_dinode_dealloc(ip);
	goto out_unlock;

out_truncate:
	gfs2_log_flush(sdp, ip->i_gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_EVICT_INODE);
	metamapping = gfs2_glock2aspace(ip->i_gl);
	if (test_bit(GLF_DIRTY, &ip->i_gl->gl_flags)) {
		filemap_fdatawrite(metamapping);
		filemap_fdatawait(metamapping);
	}
	write_inode_now(inode, 1);
	gfs2_ail_flush(ip->i_gl, 0);

	error = gfs2_trans_begin(sdp, 0, sdp->sd_jdesc->jd_blocks);
	if (error)
		goto out_unlock;
	/* Needs to be done before glock release & also in a transaction */
	truncate_inode_pages(&inode->i_data, 0);
	truncate_inode_pages(metamapping, 0);
	gfs2_trans_end(sdp);

out_unlock:
	if (gfs2_rs_active(&ip->i_res))
		gfs2_rs_deltree(&ip->i_res);

	if (gfs2_holder_initialized(&ip->i_iopen_gh)) {
		glock_clear_object(ip->i_iopen_gh.gh_gl, ip);
		if (test_bit(HIF_HOLDER, &ip->i_iopen_gh.gh_iflags)) {
			ip->i_iopen_gh.gh_flags |= GL_NOCACHE;
			gfs2_glock_dq(&ip->i_iopen_gh);
		}
		gfs2_holder_uninit(&ip->i_iopen_gh);
	}
	if (gfs2_holder_initialized(&gh)) {
		glock_clear_object(ip->i_gl, ip);
		gfs2_glock_dq_uninit(&gh);
	}
	if (error && error != GLR_TRYFAILED && error != -EROFS)
		fs_warn(sdp, "gfs2_evict_inode: %d\n", error);
out:
	truncate_inode_pages_final(&inode->i_data);
	gfs2_rsqa_delete(ip, NULL);
	gfs2_ordered_del_inode(ip);
	clear_inode(inode);
	gfs2_dir_hash_inval(ip);
	glock_clear_object(ip->i_gl, ip);
	wait_on_bit_io(&ip->i_flags, GIF_GLOP_PENDING, TASK_UNINTERRUPTIBLE);
	gfs2_glock_add_to_lru(ip->i_gl);
	gfs2_glock_put_eventually(ip->i_gl);
	ip->i_gl = NULL;
	if (gfs2_holder_initialized(&ip->i_iopen_gh)) {
		struct gfs2_glock *gl = ip->i_iopen_gh.gh_gl;

		glock_clear_object(gl, ip);
		ip->i_iopen_gh.gh_flags |= GL_NOCACHE;
		gfs2_glock_hold(gl);
		gfs2_glock_dq_uninit(&ip->i_iopen_gh);
		gfs2_glock_put_eventually(gl);
	}
}