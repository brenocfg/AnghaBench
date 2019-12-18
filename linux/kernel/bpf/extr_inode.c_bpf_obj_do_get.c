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
struct path {int /*<<< orphan*/  dentry; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct filename {int /*<<< orphan*/  name; } ;
typedef  enum bpf_type { ____Placeholder_bpf_type } bpf_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_MODE (int) ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 void* bpf_any_get (int /*<<< orphan*/ ,int) ; 
 int bpf_inode_type (struct inode*,int*) ; 
 struct inode* d_backing_inode (int /*<<< orphan*/ ) ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int kern_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  touch_atime (struct path*) ; 

__attribute__((used)) static void *bpf_obj_do_get(const struct filename *pathname,
			    enum bpf_type *type, int flags)
{
	struct inode *inode;
	struct path path;
	void *raw;
	int ret;

	ret = kern_path(pathname->name, LOOKUP_FOLLOW, &path);
	if (ret)
		return ERR_PTR(ret);

	inode = d_backing_inode(path.dentry);
	ret = inode_permission(inode, ACC_MODE(flags));
	if (ret)
		goto out;

	ret = bpf_inode_type(inode, type);
	if (ret)
		goto out;

	raw = bpf_any_get(inode->i_private, *type);
	if (!IS_ERR(raw))
		touch_atime(&path);

	path_put(&path);
	return raw;
out:
	path_put(&path);
	return ERR_PTR(ret);
}