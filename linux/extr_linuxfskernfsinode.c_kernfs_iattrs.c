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
struct kernfs_node {struct kernfs_iattrs* iattr; int /*<<< orphan*/  mode; } ;
struct iattr {int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
struct kernfs_iattrs {int /*<<< orphan*/  xattrs; struct iattr ia_iattr; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 
 struct kernfs_iattrs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_xattrs_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kernfs_iattrs *kernfs_iattrs(struct kernfs_node *kn)
{
	static DEFINE_MUTEX(iattr_mutex);
	struct kernfs_iattrs *ret;
	struct iattr *iattrs;

	mutex_lock(&iattr_mutex);

	if (kn->iattr)
		goto out_unlock;

	kn->iattr = kzalloc(sizeof(struct kernfs_iattrs), GFP_KERNEL);
	if (!kn->iattr)
		goto out_unlock;
	iattrs = &kn->iattr->ia_iattr;

	/* assign default attributes */
	iattrs->ia_mode = kn->mode;
	iattrs->ia_uid = GLOBAL_ROOT_UID;
	iattrs->ia_gid = GLOBAL_ROOT_GID;

	ktime_get_real_ts64(&iattrs->ia_atime);
	iattrs->ia_mtime = iattrs->ia_atime;
	iattrs->ia_ctime = iattrs->ia_atime;

	simple_xattrs_init(&kn->iattr->xattrs);
out_unlock:
	ret = kn->iattr;
	mutex_unlock(&iattr_mutex);
	return ret;
}