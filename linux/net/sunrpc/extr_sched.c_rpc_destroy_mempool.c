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

/* Variables and functions */
 int /*<<< orphan*/  delay_queue ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_buffer_mempool ; 
 int /*<<< orphan*/  rpc_buffer_slabp ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_task_mempool ; 
 int /*<<< orphan*/  rpc_task_slabp ; 
 int /*<<< orphan*/  rpciod_stop () ; 

void
rpc_destroy_mempool(void)
{
	rpciod_stop();
	mempool_destroy(rpc_buffer_mempool);
	mempool_destroy(rpc_task_mempool);
	kmem_cache_destroy(rpc_task_slabp);
	kmem_cache_destroy(rpc_buffer_slabp);
	rpc_destroy_wait_queue(&delay_queue);
}