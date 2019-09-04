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
struct TYPE_2__ {int /*<<< orphan*/  mnt_flags; } ;
struct mount {TYPE_1__ mnt; int /*<<< orphan*/ * mnt_master; int /*<<< orphan*/  mnt_slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_UNBINDABLE ; 
 int MS_SHARED ; 
 int MS_SLAVE ; 
 int MS_UNBINDABLE ; 
 int /*<<< orphan*/  do_make_slave (struct mount*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mnt_shared (struct mount*) ; 

void change_mnt_propagation(struct mount *mnt, int type)
{
	if (type == MS_SHARED) {
		set_mnt_shared(mnt);
		return;
	}
	do_make_slave(mnt);
	if (type != MS_SLAVE) {
		list_del_init(&mnt->mnt_slave);
		mnt->mnt_master = NULL;
		if (type == MS_UNBINDABLE)
			mnt->mnt.mnt_flags |= MNT_UNBINDABLE;
		else
			mnt->mnt.mnt_flags &= ~MNT_UNBINDABLE;
	}
}