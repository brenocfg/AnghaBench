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
struct qstr {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_mode; } ;
struct fsnotify_iter_info {int dummy; } ;
struct fsnotify_group {int dummy; } ;

/* Variables and functions */
 int FS_ATTRIB ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nfsd_file_close_inode (struct inode*) ; 
 int /*<<< orphan*/  trace_nfsd_file_fsnotify_handle_event (struct inode*,int) ; 

__attribute__((used)) static int
nfsd_file_fsnotify_handle_event(struct fsnotify_group *group,
				struct inode *inode,
				u32 mask, const void *data, int data_type,
				const struct qstr *file_name, u32 cookie,
				struct fsnotify_iter_info *iter_info)
{
	trace_nfsd_file_fsnotify_handle_event(inode, mask);

	/* Should be no marks on non-regular files */
	if (!S_ISREG(inode->i_mode)) {
		WARN_ON_ONCE(1);
		return 0;
	}

	/* don't close files if this was not the last link */
	if (mask & FS_ATTRIB) {
		if (inode->i_nlink)
			return 0;
	}

	nfsd_file_close_inode(inode);
	return 0;
}