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
struct ida {int /*<<< orphan*/  ida_rt; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOSPC ; 
 unsigned int INT_MAX ; 
 int ida_get_new_above (struct ida*,unsigned int) ; 
 int /*<<< orphan*/  ida_pre_get (struct ida*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (struct ida*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ida_alloc_range(struct ida *ida, unsigned int min, unsigned int max,
			gfp_t gfp)
{
	int id = 0;
	unsigned long flags;

	if ((int)min < 0)
		return -ENOSPC;

	if ((int)max < 0)
		max = INT_MAX;

again:
	xa_lock_irqsave(&ida->ida_rt, flags);
	id = ida_get_new_above(ida, min);
	if (id > (int)max) {
		ida_remove(ida, id);
		id = -ENOSPC;
	}
	xa_unlock_irqrestore(&ida->ida_rt, flags);

	if (unlikely(id == -EAGAIN)) {
		if (!ida_pre_get(ida, gfp))
			return -ENOMEM;
		goto again;
	}

	return id;
}