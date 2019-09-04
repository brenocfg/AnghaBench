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
struct inode {int dummy; } ;
struct file {struct ceph_file_info* private_data; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/ * i_nr_by_mode; } ;
struct ceph_file_info {int fmode; } ;

/* Variables and functions */
 int CEPH_FILE_MODE_LAZY ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct file*) ; 
 size_t ffs (int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ceph_ioctl_lazyio(struct file *file)
{
	struct ceph_file_info *fi = file->private_data;
	struct inode *inode = file_inode(file);
	struct ceph_inode_info *ci = ceph_inode(inode);

	if ((fi->fmode & CEPH_FILE_MODE_LAZY) == 0) {
		spin_lock(&ci->i_ceph_lock);
		fi->fmode |= CEPH_FILE_MODE_LAZY;
		ci->i_nr_by_mode[ffs(CEPH_FILE_MODE_LAZY)]++;
		spin_unlock(&ci->i_ceph_lock);
		dout("ioctl_layzio: file %p marked lazy\n", file);

		ceph_check_caps(ci, 0, NULL);
	} else {
		dout("ioctl_layzio: file %p already lazy\n", file);
	}
	return 0;
}