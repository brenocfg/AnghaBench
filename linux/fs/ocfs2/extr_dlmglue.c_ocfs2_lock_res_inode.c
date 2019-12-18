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
struct ocfs2_lock_res {scalar_t__ l_priv; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ocfs2_is_inode_lock (struct ocfs2_lock_res*) ; 

__attribute__((used)) static inline struct inode *ocfs2_lock_res_inode(struct ocfs2_lock_res *lockres)
{
	BUG_ON(!ocfs2_is_inode_lock(lockres));

	return (struct inode *) lockres->l_priv;
}