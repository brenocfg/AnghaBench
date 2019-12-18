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
struct cifsLockInfo {int /*<<< orphan*/  block_q; int /*<<< orphan*/  blist; int /*<<< orphan*/  flags; int /*<<< orphan*/  pid; int /*<<< orphan*/  type; void* length; void* offset; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  void* __u64 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct cifsLockInfo* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cifsLockInfo *
cifs_lock_init(__u64 offset, __u64 length, __u8 type, __u16 flags)
{
	struct cifsLockInfo *lock =
		kmalloc(sizeof(struct cifsLockInfo), GFP_KERNEL);
	if (!lock)
		return lock;
	lock->offset = offset;
	lock->length = length;
	lock->type = type;
	lock->pid = current->tgid;
	lock->flags = flags;
	INIT_LIST_HEAD(&lock->blist);
	init_waitqueue_head(&lock->block_q);
	return lock;
}