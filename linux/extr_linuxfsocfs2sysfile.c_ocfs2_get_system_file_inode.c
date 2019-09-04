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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  system_file_mutex; struct inode** global_system_inodes; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct inode* _ocfs2_get_system_file_inode (struct ocfs2_super*,int,int /*<<< orphan*/ ) ; 
 struct inode** get_local_system_inode (struct ocfs2_super*,int,int /*<<< orphan*/ ) ; 
 struct inode* igrab (struct inode*) ; 
 scalar_t__ is_global_system_inode (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct inode *ocfs2_get_system_file_inode(struct ocfs2_super *osb,
					  int type,
					  u32 slot)
{
	struct inode *inode = NULL;
	struct inode **arr = NULL;

	/* avoid the lookup if cached in local system file array */
	if (is_global_system_inode(type)) {
		arr = &(osb->global_system_inodes[type]);
	} else
		arr = get_local_system_inode(osb, type, slot);

	mutex_lock(&osb->system_file_mutex);
	if (arr && ((inode = *arr) != NULL)) {
		/* get a ref in addition to the array ref */
		inode = igrab(inode);
		mutex_unlock(&osb->system_file_mutex);
		BUG_ON(!inode);

		return inode;
	}

	/* this gets one ref thru iget */
	inode = _ocfs2_get_system_file_inode(osb, type, slot);

	/* add one more if putting into array for first time */
	if (arr && inode) {
		*arr = igrab(inode);
		BUG_ON(!*arr);
	}
	mutex_unlock(&osb->system_file_mutex);
	return inode;
}