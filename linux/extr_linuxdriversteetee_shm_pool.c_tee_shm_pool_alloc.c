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
struct tee_shm_pool {struct tee_shm_pool_mgr* dma_buf_mgr; struct tee_shm_pool_mgr* private_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tee_shm_pool* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  check_mgr_ops (struct tee_shm_pool_mgr*) ; 
 struct tee_shm_pool* kzalloc (int,int /*<<< orphan*/ ) ; 

struct tee_shm_pool *tee_shm_pool_alloc(struct tee_shm_pool_mgr *priv_mgr,
					struct tee_shm_pool_mgr *dmabuf_mgr)
{
	struct tee_shm_pool *pool;

	if (!check_mgr_ops(priv_mgr) || !check_mgr_ops(dmabuf_mgr))
		return ERR_PTR(-EINVAL);

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return ERR_PTR(-ENOMEM);

	pool->private_mgr = priv_mgr;
	pool->dma_buf_mgr = dmabuf_mgr;

	return pool;
}