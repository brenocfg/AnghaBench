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
struct TYPE_2__ {int /*<<< orphan*/ * mnt_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct vfsmount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 TYPE_1__* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void kern_unmount(struct vfsmount *mnt)
{
	/* release long term mount so mount point can be released */
	if (!IS_ERR_OR_NULL(mnt)) {
		real_mount(mnt)->mnt_ns = NULL;
		synchronize_rcu();	/* yecchhh... */
		mntput(mnt);
	}
}