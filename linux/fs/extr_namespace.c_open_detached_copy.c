#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct user_namespace {int dummy; } ;
struct path {int /*<<< orphan*/ * mnt; } ;
struct mount {int /*<<< orphan*/  f_mode; int /*<<< orphan*/  mnt; int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  list; struct mount* root; int /*<<< orphan*/  mounts; struct mount* mnt_ns; } ;
struct mnt_namespace {int /*<<< orphan*/  f_mode; int /*<<< orphan*/  mnt; int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  list; struct mnt_namespace* root; int /*<<< orphan*/  mounts; struct mnt_namespace* mnt_ns; } ;
struct file {int /*<<< orphan*/  f_mode; int /*<<< orphan*/  mnt; int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  list; struct file* root; int /*<<< orphan*/  mounts; struct file* mnt_ns; } ;
struct TYPE_6__ {TYPE_2__* nsproxy; } ;
struct TYPE_5__ {TYPE_1__* mnt_ns; } ;
struct TYPE_4__ {struct user_namespace* user_ns; } ;

/* Variables and functions */
 struct mount* ERR_CAST (struct mount*) ; 
 int /*<<< orphan*/  FMODE_NEED_UNMOUNT ; 
 scalar_t__ IS_ERR (struct mount*) ; 
 int /*<<< orphan*/  O_PATH ; 
 struct mount* __do_loopback (struct path*,int) ; 
 struct mount* alloc_mnt_ns (struct user_namespace*,int) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  current_cred () ; 
 struct mount* dentry_open (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dissolve_on_fput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mnt_ns (struct mount*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  mntget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 struct mount* next_mnt (struct mount*,struct mount*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static struct file *open_detached_copy(struct path *path, bool recursive)
{
	struct user_namespace *user_ns = current->nsproxy->mnt_ns->user_ns;
	struct mnt_namespace *ns = alloc_mnt_ns(user_ns, true);
	struct mount *mnt, *p;
	struct file *file;

	if (IS_ERR(ns))
		return ERR_CAST(ns);

	namespace_lock();
	mnt = __do_loopback(path, recursive);
	if (IS_ERR(mnt)) {
		namespace_unlock();
		free_mnt_ns(ns);
		return ERR_CAST(mnt);
	}

	lock_mount_hash();
	for (p = mnt; p; p = next_mnt(p, mnt)) {
		p->mnt_ns = ns;
		ns->mounts++;
	}
	ns->root = mnt;
	list_add_tail(&ns->list, &mnt->mnt_list);
	mntget(&mnt->mnt);
	unlock_mount_hash();
	namespace_unlock();

	mntput(path->mnt);
	path->mnt = &mnt->mnt;
	file = dentry_open(path, O_PATH, current_cred());
	if (IS_ERR(file))
		dissolve_on_fput(path->mnt);
	else
		file->f_mode |= FMODE_NEED_UNMOUNT;
	return file;
}