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
struct TYPE_2__ {int mnt_flags; } ;
struct mount {TYPE_1__ mnt; int /*<<< orphan*/  mnt_expire; } ;

/* Variables and functions */
 int MNT_LOCKED ; 
 int MNT_LOCK_ATIME ; 
 int MNT_LOCK_NODEV ; 
 int MNT_LOCK_NOEXEC ; 
 int MNT_LOCK_NOSUID ; 
 int MNT_LOCK_READONLY ; 
 int MNT_NODEV ; 
 int MNT_NOEXEC ; 
 int MNT_NOSUID ; 
 int MNT_READONLY ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct mount* next_mnt (struct mount*,struct mount*) ; 

__attribute__((used)) static void lock_mnt_tree(struct mount *mnt)
{
	struct mount *p;

	for (p = mnt; p; p = next_mnt(p, mnt)) {
		int flags = p->mnt.mnt_flags;
		/* Don't allow unprivileged users to change mount flags */
		flags |= MNT_LOCK_ATIME;

		if (flags & MNT_READONLY)
			flags |= MNT_LOCK_READONLY;

		if (flags & MNT_NODEV)
			flags |= MNT_LOCK_NODEV;

		if (flags & MNT_NOSUID)
			flags |= MNT_LOCK_NOSUID;

		if (flags & MNT_NOEXEC)
			flags |= MNT_LOCK_NOEXEC;
		/* Don't allow unprivileged users to reveal what is under a mount */
		if (list_empty(&p->mnt_expire))
			flags |= MNT_LOCKED;
		p->mnt.mnt_flags = flags;
	}
}