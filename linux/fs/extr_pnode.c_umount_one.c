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
struct mount {int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  mnt_umounting; int /*<<< orphan*/  mnt_child; TYPE_1__ mnt; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_MNT_MARK (struct mount*) ; 
 int /*<<< orphan*/  MNT_UMOUNT ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void umount_one(struct mount *mnt, struct list_head *to_umount)
{
	CLEAR_MNT_MARK(mnt);
	mnt->mnt.mnt_flags |= MNT_UMOUNT;
	list_del_init(&mnt->mnt_child);
	list_del_init(&mnt->mnt_umounting);
	list_move_tail(&mnt->mnt_list, to_umount);
}