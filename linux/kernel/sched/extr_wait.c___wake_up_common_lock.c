#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {long flags; int /*<<< orphan*/  entry; int /*<<< orphan*/ * func; int /*<<< orphan*/ * private; } ;
typedef  TYPE_1__ wait_queue_entry_t ;
struct wait_queue_head {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 long WQ_FLAG_BOOKMARK ; 
 int __wake_up_common (struct wait_queue_head*,unsigned int,int,int,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __wake_up_common_lock(struct wait_queue_head *wq_head, unsigned int mode,
			int nr_exclusive, int wake_flags, void *key)
{
	unsigned long flags;
	wait_queue_entry_t bookmark;

	bookmark.flags = 0;
	bookmark.private = NULL;
	bookmark.func = NULL;
	INIT_LIST_HEAD(&bookmark.entry);

	do {
		spin_lock_irqsave(&wq_head->lock, flags);
		nr_exclusive = __wake_up_common(wq_head, mode, nr_exclusive,
						wake_flags, key, &bookmark);
		spin_unlock_irqrestore(&wq_head->lock, flags);
	} while (bookmark.flags & WQ_FLAG_BOOKMARK);
}