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
struct dentry {int dummy; } ;
struct cachefiles_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int security_inode_create (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int security_inode_mkdir (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cachefiles_check_cache_dir(struct cachefiles_cache *cache,
				      struct dentry *root)
{
	int ret;

	ret = security_inode_mkdir(d_backing_inode(root), root, 0);
	if (ret < 0) {
		pr_err("Security denies permission to make dirs: error %d",
		       ret);
		return ret;
	}

	ret = security_inode_create(d_backing_inode(root), root, 0);
	if (ret < 0)
		pr_err("Security denies permission to create files: error %d",
		       ret);

	return ret;
}