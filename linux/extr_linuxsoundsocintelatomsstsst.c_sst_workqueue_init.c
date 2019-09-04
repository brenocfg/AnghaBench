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
struct intel_sst_drv {int /*<<< orphan*/  post_msg_wq; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  ipc_post_msg_wq; int /*<<< orphan*/  block_list; int /*<<< orphan*/  ipc_dispatch_list; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  memcpy_list; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_process_pending_msg ; 

__attribute__((used)) static int sst_workqueue_init(struct intel_sst_drv *ctx)
{
	INIT_LIST_HEAD(&ctx->memcpy_list);
	INIT_LIST_HEAD(&ctx->rx_list);
	INIT_LIST_HEAD(&ctx->ipc_dispatch_list);
	INIT_LIST_HEAD(&ctx->block_list);
	INIT_WORK(&ctx->ipc_post_msg_wq, sst_process_pending_msg);
	init_waitqueue_head(&ctx->wait_queue);

	ctx->post_msg_wq =
		create_singlethread_workqueue("sst_post_msg_wq");
	if (!ctx->post_msg_wq)
		return -EBUSY;
	return 0;
}