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
struct inode_security_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  initialized; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LABEL_INVALID ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void selinux_inode_invalidate_secctx(struct inode *inode)
{
	struct inode_security_struct *isec = selinux_inode(inode);

	spin_lock(&isec->lock);
	isec->initialized = LABEL_INVALID;
	spin_unlock(&isec->lock);
}