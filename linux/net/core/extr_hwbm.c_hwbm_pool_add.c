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
struct hwbm_pool {scalar_t__ buf_num; scalar_t__ size; int /*<<< orphan*/  buf_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hwbm_pool_refill (struct hwbm_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

int hwbm_pool_add(struct hwbm_pool *bm_pool, unsigned int buf_num)
{
	int err, i;

	mutex_lock(&bm_pool->buf_lock);
	if (bm_pool->buf_num == bm_pool->size) {
		pr_warn("pool already filled\n");
		mutex_unlock(&bm_pool->buf_lock);
		return bm_pool->buf_num;
	}

	if (buf_num + bm_pool->buf_num > bm_pool->size) {
		pr_warn("cannot allocate %d buffers for pool\n",
			buf_num);
		mutex_unlock(&bm_pool->buf_lock);
		return 0;
	}

	if ((buf_num + bm_pool->buf_num) < bm_pool->buf_num) {
		pr_warn("Adding %d buffers to the %d current buffers will overflow\n",
			buf_num,  bm_pool->buf_num);
		mutex_unlock(&bm_pool->buf_lock);
		return 0;
	}

	for (i = 0; i < buf_num; i++) {
		err = hwbm_pool_refill(bm_pool, GFP_KERNEL);
		if (err < 0)
			break;
	}

	/* Update BM driver with number of buffers added to pool */
	bm_pool->buf_num += i;

	pr_debug("hwpm pool: %d of %d buffers added\n", i, buf_num);
	mutex_unlock(&bm_pool->buf_lock);

	return i;
}