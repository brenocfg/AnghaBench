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
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 char* ecryptfs_readlink_lower (struct dentry*,size_t*) ; 
 int /*<<< orphan*/  fsstack_copy_attr_atime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_link ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *ecryptfs_get_link(struct dentry *dentry,
				     struct inode *inode,
				     struct delayed_call *done)
{
	size_t len;
	char *buf;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	buf = ecryptfs_readlink_lower(dentry, &len);
	if (IS_ERR(buf))
		return buf;
	fsstack_copy_attr_atime(d_inode(dentry),
				d_inode(ecryptfs_dentry_to_lower(dentry)));
	buf[len] = '\0';
	set_delayed_call(done, kfree_link, buf);
	return buf;
}