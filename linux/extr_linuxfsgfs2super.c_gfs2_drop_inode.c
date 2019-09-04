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
struct inode {scalar_t__ i_nlink; } ;
struct TYPE_3__ {struct gfs2_glock* gh_gl; } ;
struct gfs2_inode {TYPE_1__ i_iopen_gh; int /*<<< orphan*/  i_flags; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_delete; int /*<<< orphan*/  gl_flags; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GIF_FREE_VFS_INODE ; 
 int /*<<< orphan*/  GLF_DEMOTE ; 
 int PF_MEMALLOC ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 TYPE_2__* current ; 
 int generic_drop_inode (struct inode*) ; 
 int /*<<< orphan*/  gfs2_delete_workqueue ; 
 int /*<<< orphan*/  gfs2_glock_hold (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_queue_put (struct gfs2_glock*) ; 
 scalar_t__ gfs2_holder_initialized (TYPE_1__*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfs2_drop_inode(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);

	if (!test_bit(GIF_FREE_VFS_INODE, &ip->i_flags) &&
	    inode->i_nlink &&
	    gfs2_holder_initialized(&ip->i_iopen_gh)) {
		struct gfs2_glock *gl = ip->i_iopen_gh.gh_gl;
		if (test_bit(GLF_DEMOTE, &gl->gl_flags))
			clear_nlink(inode);
	}

	/*
	 * When under memory pressure when an inode's link count has dropped to
	 * zero, defer deleting the inode to the delete workqueue.  This avoids
	 * calling into DLM under memory pressure, which can deadlock.
	 */
	if (!inode->i_nlink &&
	    unlikely(current->flags & PF_MEMALLOC) &&
	    gfs2_holder_initialized(&ip->i_iopen_gh)) {
		struct gfs2_glock *gl = ip->i_iopen_gh.gh_gl;

		gfs2_glock_hold(gl);
		if (queue_work(gfs2_delete_workqueue, &gl->gl_delete) == 0)
			gfs2_glock_queue_put(gl);
		return false;
	}

	return generic_drop_inode(inode);
}