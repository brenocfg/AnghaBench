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
struct kernfs_node {struct kernfs_iattrs* iattr; } ;
struct kernfs_iattrs {int /*<<< orphan*/  xattrs; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  kernfs_iattrs_cache ; 
 struct kernfs_iattrs* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_xattrs_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kernfs_iattrs *__kernfs_iattrs(struct kernfs_node *kn, int alloc)
{
	static DEFINE_MUTEX(iattr_mutex);
	struct kernfs_iattrs *ret;

	mutex_lock(&iattr_mutex);

	if (kn->iattr || !alloc)
		goto out_unlock;

	kn->iattr = kmem_cache_zalloc(kernfs_iattrs_cache, GFP_KERNEL);
	if (!kn->iattr)
		goto out_unlock;

	/* assign default attributes */
	kn->iattr->ia_uid = GLOBAL_ROOT_UID;
	kn->iattr->ia_gid = GLOBAL_ROOT_GID;

	ktime_get_real_ts64(&kn->iattr->ia_atime);
	kn->iattr->ia_mtime = kn->iattr->ia_atime;
	kn->iattr->ia_ctime = kn->iattr->ia_atime;

	simple_xattrs_init(&kn->iattr->xattrs);
out_unlock:
	ret = kn->iattr;
	mutex_unlock(&iattr_mutex);
	return ret;
}