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
struct cifsLockInfo {int /*<<< orphan*/  llist; } ;
struct cifsInodeInfo {int /*<<< orphan*/  lock_sem; } ;
struct cifsFileInfo {TYPE_1__* llist; int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  locks; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cifs_lock_add(struct cifsFileInfo *cfile, struct cifsLockInfo *lock)
{
	struct cifsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	cifs_down_write(&cinode->lock_sem);
	list_add_tail(&lock->llist, &cfile->llist->locks);
	up_write(&cinode->lock_sem);
}