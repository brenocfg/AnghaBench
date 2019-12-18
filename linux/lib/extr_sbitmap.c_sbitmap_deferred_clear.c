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
struct sbitmap {TYPE_1__* map; } ;
struct TYPE_2__ {unsigned long word; int /*<<< orphan*/  swap_lock; int /*<<< orphan*/  cleared; } ;

/* Variables and functions */
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool sbitmap_deferred_clear(struct sbitmap *sb, int index)
{
	unsigned long mask, val;
	bool ret = false;
	unsigned long flags;

	spin_lock_irqsave(&sb->map[index].swap_lock, flags);

	if (!sb->map[index].cleared)
		goto out_unlock;

	/*
	 * First get a stable cleared mask, setting the old mask to 0.
	 */
	mask = xchg(&sb->map[index].cleared, 0);

	/*
	 * Now clear the masked bits in our free word
	 */
	do {
		val = sb->map[index].word;
	} while (cmpxchg(&sb->map[index].word, val, val & ~mask) != val);

	ret = true;
out_unlock:
	spin_unlock_irqrestore(&sb->map[index].swap_lock, flags);
	return ret;
}