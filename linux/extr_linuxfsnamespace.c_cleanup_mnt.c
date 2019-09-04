#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mnt_sb; int /*<<< orphan*/  mnt_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  first; } ;
struct mount {int /*<<< orphan*/  mnt_rcu; TYPE_2__ mnt; TYPE_1__ mnt_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deactivate_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_free_vfsmnt ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_vfsmount_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  mnt_free_id (struct mount*) ; 
 int /*<<< orphan*/  mnt_get_writers (struct mount*) ; 
 int /*<<< orphan*/  mnt_pin_kill (struct mount*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_mnt(struct mount *mnt)
{
	/*
	 * This probably indicates that somebody messed
	 * up a mnt_want/drop_write() pair.  If this
	 * happens, the filesystem was probably unable
	 * to make r/w->r/o transitions.
	 */
	/*
	 * The locking used to deal with mnt_count decrement provides barriers,
	 * so mnt_get_writers() below is safe.
	 */
	WARN_ON(mnt_get_writers(mnt));
	if (unlikely(mnt->mnt_pins.first))
		mnt_pin_kill(mnt);
	fsnotify_vfsmount_delete(&mnt->mnt);
	dput(mnt->mnt.mnt_root);
	deactivate_super(mnt->mnt.mnt_sb);
	mnt_free_id(mnt);
	call_rcu(&mnt->mnt_rcu, delayed_free_vfsmnt);
}