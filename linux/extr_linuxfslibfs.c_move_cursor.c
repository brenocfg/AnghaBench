#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_subdirs; TYPE_2__ d_child; TYPE_1__* d_inode; struct dentry* d_parent; } ;
struct TYPE_4__ {unsigned int i_dir_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __list_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int cmpxchg (unsigned int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  list_add (TYPE_2__*,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void move_cursor(struct dentry *cursor, struct list_head *after)
{
	struct dentry *parent = cursor->d_parent;
	unsigned n, *seq = &parent->d_inode->i_dir_seq;
	spin_lock(&parent->d_lock);
	for (;;) {
		n = *seq;
		if (!(n & 1) && cmpxchg(seq, n, n + 1) == n)
			break;
		cpu_relax();
	}
	__list_del(cursor->d_child.prev, cursor->d_child.next);
	if (after)
		list_add(&cursor->d_child, after);
	else
		list_add_tail(&cursor->d_child, &parent->d_subdirs);
	smp_store_release(seq, n + 2);
	spin_unlock(&parent->d_lock);
}