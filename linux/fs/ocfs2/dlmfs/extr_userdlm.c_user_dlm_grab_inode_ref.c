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
struct user_lock_res {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 struct inode* user_dlm_inode_from_user_lockres (struct user_lock_res*) ; 

__attribute__((used)) static inline void user_dlm_grab_inode_ref(struct user_lock_res *lockres)
{
	struct inode *inode;
	inode = user_dlm_inode_from_user_lockres(lockres);
	if (!igrab(inode))
		BUG();
}