#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qstr {int dummy; } ;
struct path {TYPE_1__* dentry; } ;
struct filename {int dummy; } ;
typedef  struct filename dentry ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  EINVAL ; 
 struct filename* ERR_CAST (struct filename*) ; 
 struct filename* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct filename*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int LAST_NORM ; 
 struct filename* __lookup_hash (struct qstr*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct filename* filename_parentat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path*,struct qstr*,int*) ; 
 int /*<<< orphan*/  getname_kernel (char const*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  putname (struct filename*) ; 
 scalar_t__ unlikely (int) ; 

struct dentry *kern_path_locked(const char *name, struct path *path)
{
	struct filename *filename;
	struct dentry *d;
	struct qstr last;
	int type;

	filename = filename_parentat(AT_FDCWD, getname_kernel(name), 0, path,
				    &last, &type);
	if (IS_ERR(filename))
		return ERR_CAST(filename);
	if (unlikely(type != LAST_NORM)) {
		path_put(path);
		putname(filename);
		return ERR_PTR(-EINVAL);
	}
	inode_lock_nested(path->dentry->d_inode, I_MUTEX_PARENT);
	d = __lookup_hash(&last, path->dentry, 0);
	if (IS_ERR(d)) {
		inode_unlock(path->dentry->d_inode);
		path_put(path);
	}
	putname(filename);
	return d;
}