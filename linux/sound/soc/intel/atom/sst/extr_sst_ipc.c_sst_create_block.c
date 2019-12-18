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
typedef  void* u32 ;
struct sst_block {int condition; int on; int /*<<< orphan*/  node; void* drv_id; void* msg_id; } ;
struct intel_sst_drv {int /*<<< orphan*/  block_lock; int /*<<< orphan*/  block_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct sst_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct sst_block *sst_create_block(struct intel_sst_drv *ctx,
					u32 msg_id, u32 drv_id)
{
	struct sst_block *msg = NULL;

	dev_dbg(ctx->dev, "Enter\n");
	msg = kzalloc(sizeof(*msg), GFP_KERNEL);
	if (!msg)
		return NULL;
	msg->condition = false;
	msg->on = true;
	msg->msg_id = msg_id;
	msg->drv_id = drv_id;
	spin_lock_bh(&ctx->block_lock);
	list_add_tail(&msg->node, &ctx->block_list);
	spin_unlock_bh(&ctx->block_lock);

	return msg;
}