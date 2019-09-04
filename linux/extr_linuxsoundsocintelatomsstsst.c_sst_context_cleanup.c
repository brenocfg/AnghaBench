#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ list_len; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
struct intel_sst_drv {int /*<<< orphan*/ * fw_in_mem; TYPE_1__ fw_sg_list; int /*<<< orphan*/  qos; int /*<<< orphan*/  post_msg_wq; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_SHUTDOWN ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_2__*) ; 
 int /*<<< orphan*/  sst_fw_version_attr_group ; 
 int /*<<< orphan*/  sst_memcpy_free_resources (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  sst_set_fw_state_locked (struct intel_sst_drv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void sst_context_cleanup(struct intel_sst_drv *ctx)
{
	pm_runtime_get_noresume(ctx->dev);
	pm_runtime_disable(ctx->dev);
	sst_unregister(ctx->dev);
	sst_set_fw_state_locked(ctx, SST_SHUTDOWN);
	sysfs_remove_group(&ctx->dev->kobj, &sst_fw_version_attr_group);
	flush_scheduled_work();
	destroy_workqueue(ctx->post_msg_wq);
	pm_qos_remove_request(ctx->qos);
	kfree(ctx->fw_sg_list.src);
	kfree(ctx->fw_sg_list.dst);
	ctx->fw_sg_list.list_len = 0;
	kfree(ctx->fw_in_mem);
	ctx->fw_in_mem = NULL;
	sst_memcpy_free_resources(ctx);
	ctx = NULL;
}