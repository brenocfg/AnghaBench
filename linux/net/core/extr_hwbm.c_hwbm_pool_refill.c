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
struct hwbm_pool {int frag_size; scalar_t__ (* construct ) (struct hwbm_pool*,void*) ;} ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  hwbm_buf_free (struct hwbm_pool*,void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 void* netdev_alloc_frag (int) ; 
 scalar_t__ stub1 (struct hwbm_pool*,void*) ; 

int hwbm_pool_refill(struct hwbm_pool *bm_pool, gfp_t gfp)
{
	int frag_size = bm_pool->frag_size;
	void *buf;

	if (likely(frag_size <= PAGE_SIZE))
		buf = netdev_alloc_frag(frag_size);
	else
		buf = kmalloc(frag_size, gfp);

	if (!buf)
		return -ENOMEM;

	if (bm_pool->construct)
		if (bm_pool->construct(bm_pool, buf)) {
			hwbm_buf_free(bm_pool, buf);
			return -ENOMEM;
		}

	return 0;
}