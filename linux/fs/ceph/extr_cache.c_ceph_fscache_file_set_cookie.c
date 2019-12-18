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
struct file {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  fscache; int /*<<< orphan*/  i_vino; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_fscache_can_enable ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct file*) ; 
 scalar_t__ fscache_cookie_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_cookie_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_disable_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fscache_enable_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  fscache_uncache_all_inode_pages (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 scalar_t__ inode_is_open_for_write (struct inode*) ; 

void ceph_fscache_file_set_cookie(struct inode *inode, struct file *filp)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	if (!fscache_cookie_valid(ci->fscache))
		return;

	if (inode_is_open_for_write(inode)) {
		dout("fscache_file_set_cookie %p %p disabling cache\n",
		     inode, filp);
		fscache_disable_cookie(ci->fscache, &ci->i_vino, false);
		fscache_uncache_all_inode_pages(ci->fscache, inode);
	} else {
		fscache_enable_cookie(ci->fscache, &ci->i_vino, i_size_read(inode),
				      ceph_fscache_can_enable, inode);
		if (fscache_cookie_enabled(ci->fscache)) {
			dout("fscache_file_set_cookie %p %p enabling cache\n",
			     inode, filp);
		}
	}
}