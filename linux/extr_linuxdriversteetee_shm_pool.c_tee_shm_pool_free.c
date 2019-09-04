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
struct tee_shm_pool {scalar_t__ dma_buf_mgr; scalar_t__ private_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tee_shm_pool*) ; 
 int /*<<< orphan*/  tee_shm_pool_mgr_destroy (scalar_t__) ; 

void tee_shm_pool_free(struct tee_shm_pool *pool)
{
	if (pool->private_mgr)
		tee_shm_pool_mgr_destroy(pool->private_mgr);
	if (pool->dma_buf_mgr)
		tee_shm_pool_mgr_destroy(pool->dma_buf_mgr);
	kfree(pool);
}