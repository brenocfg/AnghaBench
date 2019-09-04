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
struct hwbm_pool {scalar_t__ buf_num; scalar_t__ size; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int hwbm_pool_refill (struct hwbm_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int hwbm_pool_add(struct hwbm_pool *bm_pool, unsigned int buf_num, gfp_t gfp)
{
	int err, i;
	unsigned long flags;

	spin_lock_irqsave(&bm_pool->lock, flags);
	if (bm_pool->buf_num == bm_pool->size) {
		pr_warn("pool already filled\n");
		spin_unlock_irqrestore(&bm_pool->lock, flags);
		return bm_pool->buf_num;
	}

	if (buf_num + bm_pool->buf_num > bm_pool->size) {
		pr_warn("cannot allocate %d buffers for pool\n",
			buf_num);
		spin_unlock_irqrestore(&bm_pool->lock, flags);
		return 0;
	}

	if ((buf_num + bm_pool->buf_num) < bm_pool->buf_num) {
		pr_warn("Adding %d buffers to the %d current buffers will overflow\n",
			buf_num,  bm_pool->buf_num);
		spin_unlock_irqrestore(&bm_pool->lock, flags);
		return 0;
	}

	for (i = 0; i < buf_num; i++) {
		err = hwbm_pool_refill(bm_pool, gfp);
		if (err < 0)
			break;
	}

	/* Update BM driver with number of buffers added to pool */
	bm_pool->buf_num += i;

	pr_debug("hwpm pool: %d of %d buffers added\n", i, buf_num);
	spin_unlock_irqrestore(&bm_pool->lock, flags);

	return i;
}