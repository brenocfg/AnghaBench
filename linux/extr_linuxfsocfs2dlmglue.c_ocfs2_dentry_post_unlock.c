#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_dentry_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_dentry_lock_put (struct ocfs2_super*,struct ocfs2_dentry_lock*) ; 
 struct ocfs2_dentry_lock* ocfs2_lock_res_dl (struct ocfs2_lock_res*) ; 

__attribute__((used)) static void ocfs2_dentry_post_unlock(struct ocfs2_super *osb,
				     struct ocfs2_lock_res *lockres)
{
	struct ocfs2_dentry_lock *dl = ocfs2_lock_res_dl(lockres);
	ocfs2_dentry_lock_put(osb, dl);
}