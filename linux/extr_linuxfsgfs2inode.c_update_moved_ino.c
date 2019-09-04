#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {TYPE_1__ i_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  current_time (TYPE_1__*) ; 
 int gfs2_dir_mvino (struct gfs2_inode*,int /*<<< orphan*/ *,struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_qdotdot ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (TYPE_1__*) ; 

__attribute__((used)) static int update_moved_ino(struct gfs2_inode *ip, struct gfs2_inode *ndip,
			    int dir_rename)
{
	if (dir_rename)
		return gfs2_dir_mvino(ip, &gfs2_qdotdot, ndip, DT_DIR);

	ip->i_inode.i_ctime = current_time(&ip->i_inode);
	mark_inode_dirty_sync(&ip->i_inode);
	return 0;
}