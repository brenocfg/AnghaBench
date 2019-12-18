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
struct mountpoint {int /*<<< orphan*/  m_dentry; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_root; TYPE_1__* mnt_sb; } ;
struct mount {TYPE_2__ mnt; } ;
struct TYPE_3__ {int s_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTDIR ; 
 int SB_NOUSER ; 
 int attach_recursive_mnt (struct mount*,struct mount*,struct mountpoint*,int) ; 
 scalar_t__ d_is_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int graft_tree(struct mount *mnt, struct mount *p, struct mountpoint *mp)
{
	if (mnt->mnt.mnt_sb->s_flags & SB_NOUSER)
		return -EINVAL;

	if (d_is_dir(mp->m_dentry) !=
	      d_is_dir(mnt->mnt.mnt_root))
		return -ENOTDIR;

	return attach_recursive_mnt(mnt, p, mp, false);
}