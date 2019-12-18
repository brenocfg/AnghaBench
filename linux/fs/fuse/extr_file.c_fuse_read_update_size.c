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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_size; } ;
struct fuse_inode {scalar_t__ attr_version; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct fuse_conn {int /*<<< orphan*/  attr_version; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_I_SIZE_UNSTABLE ; 
 scalar_t__ atomic64_inc_return (int /*<<< orphan*/ *) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_read_update_size(struct inode *inode, loff_t size,
				  u64 attr_ver)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);

	spin_lock(&fi->lock);
	if (attr_ver == fi->attr_version && size < inode->i_size &&
	    !test_bit(FUSE_I_SIZE_UNSTABLE, &fi->state)) {
		fi->attr_version = atomic64_inc_return(&fc->attr_version);
		i_size_write(inode, size);
	}
	spin_unlock(&fi->lock);
}