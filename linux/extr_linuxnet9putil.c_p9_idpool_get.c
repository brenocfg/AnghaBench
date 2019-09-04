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
struct p9_idpool {int /*<<< orphan*/  lock; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int idr_alloc (int /*<<< orphan*/ *,struct p9_idpool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int,struct p9_idpool*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int p9_idpool_get(struct p9_idpool *p)
{
	int i;
	unsigned long flags;

	idr_preload(GFP_NOFS);
	spin_lock_irqsave(&p->lock, flags);

	/* no need to store exactly p, we just need something non-null */
	i = idr_alloc(&p->pool, p, 0, 0, GFP_NOWAIT);

	spin_unlock_irqrestore(&p->lock, flags);
	idr_preload_end();
	if (i < 0)
		return -1;

	p9_debug(P9_DEBUG_MUX, " id %d pool %p\n", i, p);
	return i;
}