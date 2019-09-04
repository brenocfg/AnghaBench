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
struct mount {int mnt_count; int /*<<< orphan*/  mnt_umount; int /*<<< orphan*/  mnt_umounting; int /*<<< orphan*/  mnt_mp_list; int /*<<< orphan*/  mnt_slave; int /*<<< orphan*/  mnt_slave_list; int /*<<< orphan*/  mnt_share; int /*<<< orphan*/  mnt_expire; int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  mnt_mounts; int /*<<< orphan*/  mnt_child; int /*<<< orphan*/  mnt_hash; scalar_t__ mnt_writers; int /*<<< orphan*/  mnt_devname; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_mountpoint ; 
 int /*<<< orphan*/  init_fs_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mount*) ; 
 struct mount* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int mnt_alloc_id (struct mount*) ; 
 int /*<<< orphan*/  mnt_cache ; 
 int /*<<< orphan*/  mnt_free_id (struct mount*) ; 

__attribute__((used)) static struct mount *alloc_vfsmnt(const char *name)
{
	struct mount *mnt = kmem_cache_zalloc(mnt_cache, GFP_KERNEL);
	if (mnt) {
		int err;

		err = mnt_alloc_id(mnt);
		if (err)
			goto out_free_cache;

		if (name) {
			mnt->mnt_devname = kstrdup_const(name, GFP_KERNEL);
			if (!mnt->mnt_devname)
				goto out_free_id;
		}

#ifdef CONFIG_SMP
		mnt->mnt_pcp = alloc_percpu(struct mnt_pcp);
		if (!mnt->mnt_pcp)
			goto out_free_devname;

		this_cpu_add(mnt->mnt_pcp->mnt_count, 1);
#else
		mnt->mnt_count = 1;
		mnt->mnt_writers = 0;
#endif

		INIT_HLIST_NODE(&mnt->mnt_hash);
		INIT_LIST_HEAD(&mnt->mnt_child);
		INIT_LIST_HEAD(&mnt->mnt_mounts);
		INIT_LIST_HEAD(&mnt->mnt_list);
		INIT_LIST_HEAD(&mnt->mnt_expire);
		INIT_LIST_HEAD(&mnt->mnt_share);
		INIT_LIST_HEAD(&mnt->mnt_slave_list);
		INIT_LIST_HEAD(&mnt->mnt_slave);
		INIT_HLIST_NODE(&mnt->mnt_mp_list);
		INIT_LIST_HEAD(&mnt->mnt_umounting);
		init_fs_pin(&mnt->mnt_umount, drop_mountpoint);
	}
	return mnt;

#ifdef CONFIG_SMP
out_free_devname:
	kfree_const(mnt->mnt_devname);
#endif
out_free_id:
	mnt_free_id(mnt);
out_free_cache:
	kmem_cache_free(mnt_cache, mnt);
	return NULL;
}