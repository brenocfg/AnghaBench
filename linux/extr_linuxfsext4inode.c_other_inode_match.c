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
struct other_inode {int /*<<< orphan*/  orig_ino; int /*<<< orphan*/  raw_inode; } ;
struct inode {unsigned long i_ino; int i_state; int /*<<< orphan*/  i_lock; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_raw_lock; } ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_SET_XTIME (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int I_DIRTY_INODE ; 
 int I_DIRTY_TIME ; 
 int I_DIRTY_TIME_EXPIRED ; 
 int I_FREEING ; 
 int I_NEW ; 
 int I_WILL_FREE ; 
 int /*<<< orphan*/  ext4_inode_csum_set (struct inode*,int /*<<< orphan*/ ,struct ext4_inode_info*) ; 
 int /*<<< orphan*/  i_atime ; 
 int /*<<< orphan*/  i_ctime ; 
 int /*<<< orphan*/  i_mtime ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ext4_other_inode_update_time (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int other_inode_match(struct inode * inode, unsigned long ino,
			     void *data)
{
	struct other_inode *oi = (struct other_inode *) data;

	if ((inode->i_ino != ino) ||
	    (inode->i_state & (I_FREEING | I_WILL_FREE | I_NEW |
			       I_DIRTY_INODE)) ||
	    ((inode->i_state & I_DIRTY_TIME) == 0))
		return 0;
	spin_lock(&inode->i_lock);
	if (((inode->i_state & (I_FREEING | I_WILL_FREE | I_NEW |
				I_DIRTY_INODE)) == 0) &&
	    (inode->i_state & I_DIRTY_TIME)) {
		struct ext4_inode_info	*ei = EXT4_I(inode);

		inode->i_state &= ~(I_DIRTY_TIME | I_DIRTY_TIME_EXPIRED);
		spin_unlock(&inode->i_lock);

		spin_lock(&ei->i_raw_lock);
		EXT4_INODE_SET_XTIME(i_ctime, inode, oi->raw_inode);
		EXT4_INODE_SET_XTIME(i_mtime, inode, oi->raw_inode);
		EXT4_INODE_SET_XTIME(i_atime, inode, oi->raw_inode);
		ext4_inode_csum_set(inode, oi->raw_inode, ei);
		spin_unlock(&ei->i_raw_lock);
		trace_ext4_other_inode_update_time(inode, oi->orig_ino);
		return -1;
	}
	spin_unlock(&inode->i_lock);
	return -1;
}