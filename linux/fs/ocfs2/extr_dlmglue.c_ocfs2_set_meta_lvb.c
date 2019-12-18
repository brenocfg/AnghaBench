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
struct ocfs2_lock_res {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocfs2_stuff_meta_lvb (struct inode*) ; 
 struct inode* ocfs2_lock_res_inode (struct ocfs2_lock_res*) ; 

__attribute__((used)) static void ocfs2_set_meta_lvb(struct ocfs2_lock_res *lockres)
{
	struct inode *inode = ocfs2_lock_res_inode(lockres);

	__ocfs2_stuff_meta_lvb(inode);
}