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
typedef  int u32 ;
struct kstat {int /*<<< orphan*/  ino; int /*<<< orphan*/  mode; } ;
struct inode {int dummy; } ;
struct fuse_inode {int /*<<< orphan*/  orig_ino; int /*<<< orphan*/  orig_i_mode; int /*<<< orphan*/  i_time; int /*<<< orphan*/  inval_mask; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int AT_STATX_DONT_SYNC ; 
 unsigned int AT_STATX_FORCE_SYNC ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forget_all_cached_acls (struct inode*) ; 
 int fuse_do_getattr (struct inode*,struct kstat*,struct file*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int time_before64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_update_get_attr(struct inode *inode, struct file *file,
				struct kstat *stat, u32 request_mask,
				unsigned int flags)
{
	struct fuse_inode *fi = get_fuse_inode(inode);
	int err = 0;
	bool sync;

	if (flags & AT_STATX_FORCE_SYNC)
		sync = true;
	else if (flags & AT_STATX_DONT_SYNC)
		sync = false;
	else if (request_mask & READ_ONCE(fi->inval_mask))
		sync = true;
	else
		sync = time_before64(fi->i_time, get_jiffies_64());

	if (sync) {
		forget_all_cached_acls(inode);
		err = fuse_do_getattr(inode, stat, file);
	} else if (stat) {
		generic_fillattr(inode, stat);
		stat->mode = fi->orig_i_mode;
		stat->ino = fi->orig_ino;
	}

	return err;
}