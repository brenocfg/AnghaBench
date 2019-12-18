#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; } ;
struct cifsLockInfo {TYPE_2__ blist; int /*<<< orphan*/  block_q; TYPE_2__ llist; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct cifsInodeInfo {int /*<<< orphan*/  lock_sem; scalar_t__ can_cache_brlcks; } ;
struct cifsFileInfo {TYPE_1__* llist; int /*<<< orphan*/  dentry; } ;
struct TYPE_5__ {TYPE_2__ locks; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFS_LOCK_OP ; 
 int EACCES ; 
 int /*<<< orphan*/  cifs_down_write (int /*<<< orphan*/ *) ; 
 int cifs_find_lock_conflict (struct cifsFileInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifsLockInfo**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_del_init (TYPE_2__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cifs_lock_add_if(struct cifsFileInfo *cfile, struct cifsLockInfo *lock,
		 bool wait)
{
	struct cifsLockInfo *conf_lock;
	struct cifsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	bool exist;
	int rc = 0;

try_again:
	exist = false;
	cifs_down_write(&cinode->lock_sem);

	exist = cifs_find_lock_conflict(cfile, lock->offset, lock->length,
					lock->type, lock->flags, &conf_lock,
					CIFS_LOCK_OP);
	if (!exist && cinode->can_cache_brlcks) {
		list_add_tail(&lock->llist, &cfile->llist->locks);
		up_write(&cinode->lock_sem);
		return rc;
	}

	if (!exist)
		rc = 1;
	else if (!wait)
		rc = -EACCES;
	else {
		list_add_tail(&lock->blist, &conf_lock->blist);
		up_write(&cinode->lock_sem);
		rc = wait_event_interruptible(lock->block_q,
					(lock->blist.prev == &lock->blist) &&
					(lock->blist.next == &lock->blist));
		if (!rc)
			goto try_again;
		cifs_down_write(&cinode->lock_sem);
		list_del_init(&lock->blist);
	}

	up_write(&cinode->lock_sem);
	return rc;
}