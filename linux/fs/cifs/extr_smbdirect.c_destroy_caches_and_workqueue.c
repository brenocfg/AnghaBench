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
struct smbd_connection {int /*<<< orphan*/  request_cache; int /*<<< orphan*/  request_mempool; int /*<<< orphan*/  response_cache; int /*<<< orphan*/  response_mempool; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_receive_buffers (struct smbd_connection*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_caches_and_workqueue(struct smbd_connection *info)
{
	destroy_receive_buffers(info);
	destroy_workqueue(info->workqueue);
	mempool_destroy(info->response_mempool);
	kmem_cache_destroy(info->response_cache);
	mempool_destroy(info->request_mempool);
	kmem_cache_destroy(info->request_cache);
}