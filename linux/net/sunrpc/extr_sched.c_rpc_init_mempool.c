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
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RPC_BUFFER_MAXSIZE ; 
 int /*<<< orphan*/  RPC_BUFFER_POOLSIZE ; 
 int /*<<< orphan*/  RPC_TASK_POOLSIZE ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  delay_queue ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* mempool_create_slab_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rpc_buffer_mempool ; 
 int /*<<< orphan*/  rpc_buffer_slabp ; 
 int /*<<< orphan*/  rpc_destroy_mempool () ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 void* rpc_task_mempool ; 
 int /*<<< orphan*/  rpc_task_slabp ; 
 int /*<<< orphan*/  rpciod_start () ; 

int
rpc_init_mempool(void)
{
	/*
	 * The following is not strictly a mempool initialisation,
	 * but there is no harm in doing it here
	 */
	rpc_init_wait_queue(&delay_queue, "delayq");
	if (!rpciod_start())
		goto err_nomem;

	rpc_task_slabp = kmem_cache_create("rpc_tasks",
					     sizeof(struct rpc_task),
					     0, SLAB_HWCACHE_ALIGN,
					     NULL);
	if (!rpc_task_slabp)
		goto err_nomem;
	rpc_buffer_slabp = kmem_cache_create("rpc_buffers",
					     RPC_BUFFER_MAXSIZE,
					     0, SLAB_HWCACHE_ALIGN,
					     NULL);
	if (!rpc_buffer_slabp)
		goto err_nomem;
	rpc_task_mempool = mempool_create_slab_pool(RPC_TASK_POOLSIZE,
						    rpc_task_slabp);
	if (!rpc_task_mempool)
		goto err_nomem;
	rpc_buffer_mempool = mempool_create_slab_pool(RPC_BUFFER_POOLSIZE,
						      rpc_buffer_slabp);
	if (!rpc_buffer_mempool)
		goto err_nomem;
	return 0;
err_nomem:
	rpc_destroy_mempool();
	return -ENOMEM;
}