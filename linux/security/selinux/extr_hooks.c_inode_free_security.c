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
struct superblock_security_struct {int /*<<< orphan*/  isec_lock; } ;
struct inode_security_struct {int /*<<< orphan*/  list; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inode_free_security(struct inode *inode)
{
	struct inode_security_struct *isec = selinux_inode(inode);
	struct superblock_security_struct *sbsec;

	if (!isec)
		return;
	sbsec = inode->i_sb->s_security;
	/*
	 * As not all inode security structures are in a list, we check for
	 * empty list outside of the lock to make sure that we won't waste
	 * time taking a lock doing nothing.
	 *
	 * The list_del_init() function can be safely called more than once.
	 * It should not be possible for this function to be called with
	 * concurrent list_add(), but for better safety against future changes
	 * in the code, we use list_empty_careful() here.
	 */
	if (!list_empty_careful(&isec->list)) {
		spin_lock(&sbsec->isec_lock);
		list_del_init(&isec->list);
		spin_unlock(&sbsec->isec_lock);
	}
}