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
struct xattr_handler {int dummy; } ;
struct kernfs_node {int dummy; } ;
struct kernfs_iattrs {int dummy; } ;
struct inode {struct kernfs_node* i_private; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kernfs_iattrs* kernfs_iattrs (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int kernfs_node_setsecdata (struct kernfs_iattrs*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_inode_getsecctx (struct inode*,void**,int /*<<< orphan*/ *) ; 
 int security_inode_setsecurity (struct inode*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  security_release_secctx (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kernfs_security_xattr_set(const struct xattr_handler *handler,
				     struct dentry *unused, struct inode *inode,
				     const char *suffix, const void *value,
				     size_t size, int flags)
{
	struct kernfs_node *kn = inode->i_private;
	struct kernfs_iattrs *attrs;
	void *secdata;
	u32 secdata_len = 0;
	int error;

	attrs = kernfs_iattrs(kn);
	if (!attrs)
		return -ENOMEM;

	error = security_inode_setsecurity(inode, suffix, value, size, flags);
	if (error)
		return error;
	error = security_inode_getsecctx(inode, &secdata, &secdata_len);
	if (error)
		return error;

	mutex_lock(&kernfs_mutex);
	error = kernfs_node_setsecdata(attrs, &secdata, &secdata_len);
	mutex_unlock(&kernfs_mutex);

	if (secdata)
		security_release_secctx(secdata, secdata_len);
	return error;
}