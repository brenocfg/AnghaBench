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
struct TYPE_2__ {int /*<<< orphan*/  mnt_root; } ;
struct mount {TYPE_1__ mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_mount_hash () ; 
 scalar_t__ mnt_ns_loop (int /*<<< orphan*/ ) ; 
 struct mount* next_mnt (struct mount*,struct mount*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static bool check_for_nsfs_mounts(struct mount *subtree)
{
	struct mount *p;
	bool ret = false;

	lock_mount_hash();
	for (p = subtree; p; p = next_mnt(p, subtree))
		if (mnt_ns_loop(p->mnt.mnt_root))
			goto out;

	ret = true;
out:
	unlock_mount_hash();
	return ret;
}