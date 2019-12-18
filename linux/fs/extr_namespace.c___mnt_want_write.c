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
struct vfsmount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_flags; } ;
struct mount {TYPE_1__ mnt; } ;

/* Variables and functions */
 int EROFS ; 
 int MNT_WRITE_HOLD ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mnt_dec_writers (struct mount*) ; 
 int /*<<< orphan*/  mnt_inc_writers (struct mount*) ; 
 scalar_t__ mnt_is_readonly (struct vfsmount*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct mount* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 

int __mnt_want_write(struct vfsmount *m)
{
	struct mount *mnt = real_mount(m);
	int ret = 0;

	preempt_disable();
	mnt_inc_writers(mnt);
	/*
	 * The store to mnt_inc_writers must be visible before we pass
	 * MNT_WRITE_HOLD loop below, so that the slowpath can see our
	 * incremented count after it has set MNT_WRITE_HOLD.
	 */
	smp_mb();
	while (READ_ONCE(mnt->mnt.mnt_flags) & MNT_WRITE_HOLD)
		cpu_relax();
	/*
	 * After the slowpath clears MNT_WRITE_HOLD, mnt_is_readonly will
	 * be set to match its requirements. So we must not load that until
	 * MNT_WRITE_HOLD is cleared.
	 */
	smp_rmb();
	if (mnt_is_readonly(m)) {
		mnt_dec_writers(mnt);
		ret = -EROFS;
	}
	preempt_enable();

	return ret;
}