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
struct path {int /*<<< orphan*/ * mnt; int /*<<< orphan*/  dentry; } ;
struct mount {TYPE_1__* mnt_parent; int /*<<< orphan*/  mnt_mountpoint; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  unhash_mnt (struct mount*) ; 

__attribute__((used)) static void detach_mnt(struct mount *mnt, struct path *old_path)
{
	old_path->dentry = mnt->mnt_mountpoint;
	old_path->mnt = &mnt->mnt_parent->mnt;
	unhash_mnt(mnt);
}