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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {struct ocfs2_dentry_lock* l_priv; } ;
struct ocfs2_dentry_lock {TYPE_1__* dl_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocfs2_super *ocfs2_get_dentry_osb(struct ocfs2_lock_res *lockres)
{
	struct ocfs2_dentry_lock *dl = lockres->l_priv;

	return OCFS2_SB(dl->dl_inode->i_sb);
}