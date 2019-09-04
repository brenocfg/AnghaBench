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
struct vfsmount {TYPE_2__* mnt_sb; } ;
struct mnt_namespace {int /*<<< orphan*/ * user_ns; } ;
struct TYPE_6__ {TYPE_1__* nsproxy; } ;
struct TYPE_5__ {unsigned long s_iflags; } ;
struct TYPE_4__ {struct mnt_namespace* mnt_ns; } ;

/* Variables and functions */
 unsigned long SB_I_NODEV ; 
 unsigned long SB_I_NOEXEC ; 
 unsigned long SB_I_USERNS_VISIBLE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned long const) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  mnt_already_visible (struct mnt_namespace*,struct vfsmount*,int*) ; 

__attribute__((used)) static bool mount_too_revealing(struct vfsmount *mnt, int *new_mnt_flags)
{
	const unsigned long required_iflags = SB_I_NOEXEC | SB_I_NODEV;
	struct mnt_namespace *ns = current->nsproxy->mnt_ns;
	unsigned long s_iflags;

	if (ns->user_ns == &init_user_ns)
		return false;

	/* Can this filesystem be too revealing? */
	s_iflags = mnt->mnt_sb->s_iflags;
	if (!(s_iflags & SB_I_USERNS_VISIBLE))
		return false;

	if ((s_iflags & required_iflags) != required_iflags) {
		WARN_ONCE(1, "Expected s_iflags to contain 0x%lx\n",
			  required_iflags);
		return true;
	}

	return !mnt_already_visible(ns, mnt, new_mnt_flags);
}