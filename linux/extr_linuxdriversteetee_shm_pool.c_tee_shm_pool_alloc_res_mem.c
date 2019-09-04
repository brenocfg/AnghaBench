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
struct tee_shm_pool_mgr {int dummy; } ;
struct tee_shm_pool_mem_info {int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
typedef  void tee_shm_pool ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PAGE_SHIFT ; 
 void* tee_shm_pool_alloc (struct tee_shm_pool_mgr*,struct tee_shm_pool_mgr*) ; 
 void* tee_shm_pool_mgr_alloc_res_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tee_shm_pool_mgr_destroy (struct tee_shm_pool_mgr*) ; 

struct tee_shm_pool *
tee_shm_pool_alloc_res_mem(struct tee_shm_pool_mem_info *priv_info,
			   struct tee_shm_pool_mem_info *dmabuf_info)
{
	struct tee_shm_pool_mgr *priv_mgr;
	struct tee_shm_pool_mgr *dmabuf_mgr;
	void *rc;

	/*
	 * Create the pool for driver private shared memory
	 */
	rc = tee_shm_pool_mgr_alloc_res_mem(priv_info->vaddr, priv_info->paddr,
					    priv_info->size,
					    3 /* 8 byte aligned */);
	if (IS_ERR(rc))
		return rc;
	priv_mgr = rc;

	/*
	 * Create the pool for dma_buf shared memory
	 */
	rc = tee_shm_pool_mgr_alloc_res_mem(dmabuf_info->vaddr,
					    dmabuf_info->paddr,
					    dmabuf_info->size, PAGE_SHIFT);
	if (IS_ERR(rc))
		goto err_free_priv_mgr;
	dmabuf_mgr = rc;

	rc = tee_shm_pool_alloc(priv_mgr, dmabuf_mgr);
	if (IS_ERR(rc))
		goto err_free_dmabuf_mgr;

	return rc;

err_free_dmabuf_mgr:
	tee_shm_pool_mgr_destroy(dmabuf_mgr);
err_free_priv_mgr:
	tee_shm_pool_mgr_destroy(priv_mgr);

	return rc;
}