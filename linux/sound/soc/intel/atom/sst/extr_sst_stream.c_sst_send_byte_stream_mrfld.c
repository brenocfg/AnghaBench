#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sst_block {unsigned char* data; } ;
struct snd_sst_bytes_v2 {scalar_t__ type; unsigned char bytes; int /*<<< orphan*/  block; int /*<<< orphan*/  len; int /*<<< orphan*/  ipc_msg; int /*<<< orphan*/  task_id; int /*<<< orphan*/  pipe_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  res_rqd; } ;
struct TYPE_6__ {TYPE_1__ part; } ;
struct TYPE_7__ {int /*<<< orphan*/  header_low_payload; TYPE_2__ header_high; } ;
struct TYPE_8__ {TYPE_3__ p; } ;
struct ipc_post {unsigned char mailbox_data; TYPE_4__ mrfld_header; } ;
struct intel_sst_drv {int /*<<< orphan*/  pvt_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ SND_SST_BYTES_GET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct ipc_post*) ; 
 int /*<<< orphan*/  memcpy (unsigned char,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_add_to_dispatch_list_and_post (struct intel_sst_drv*,struct ipc_post*) ; 
 int sst_assign_pvt_id (struct intel_sst_drv*) ; 
 struct sst_block* sst_create_block (struct intel_sst_drv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sst_create_ipc_msg (struct ipc_post**,int) ; 
 int /*<<< orphan*/  sst_fill_header_mrfld (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sst_free_block (struct intel_sst_drv*,struct sst_block*) ; 
 int sst_wait_timeout (struct intel_sst_drv*,struct sst_block*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

int sst_send_byte_stream_mrfld(struct intel_sst_drv *sst_drv_ctx,
		struct snd_sst_bytes_v2 *bytes)
{	struct ipc_post *msg = NULL;
	u32 length;
	int pvt_id, ret = 0;
	struct sst_block *block = NULL;

	dev_dbg(sst_drv_ctx->dev,
		"type:%u ipc_msg:%u block:%u task_id:%u pipe: %#x length:%#x\n",
		bytes->type, bytes->ipc_msg, bytes->block, bytes->task_id,
		bytes->pipe_id, bytes->len);

	if (sst_create_ipc_msg(&msg, true))
		return -ENOMEM;

	pvt_id = sst_assign_pvt_id(sst_drv_ctx);
	sst_fill_header_mrfld(&msg->mrfld_header, bytes->ipc_msg,
			bytes->task_id, 1, pvt_id);
	msg->mrfld_header.p.header_high.part.res_rqd = bytes->block;
	length = bytes->len;
	msg->mrfld_header.p.header_low_payload = length;
	dev_dbg(sst_drv_ctx->dev, "length is %d\n", length);
	memcpy(msg->mailbox_data, &bytes->bytes, bytes->len);
	if (bytes->block) {
		block = sst_create_block(sst_drv_ctx, bytes->ipc_msg, pvt_id);
		if (block == NULL) {
			kfree(msg);
			ret = -ENOMEM;
			goto out;
		}
	}

	sst_add_to_dispatch_list_and_post(sst_drv_ctx, msg);
	dev_dbg(sst_drv_ctx->dev, "msg->mrfld_header.p.header_low_payload:%d",
			msg->mrfld_header.p.header_low_payload);

	if (bytes->block) {
		ret = sst_wait_timeout(sst_drv_ctx, block);
		if (ret) {
			dev_err(sst_drv_ctx->dev, "fw returned err %d\n", ret);
			sst_free_block(sst_drv_ctx, block);
			goto out;
		}
	}
	if (bytes->type == SND_SST_BYTES_GET) {
		/*
		 * copy the reply and send back
		 * we need to update only sz and payload
		 */
		if (bytes->block) {
			unsigned char *r = block->data;

			dev_dbg(sst_drv_ctx->dev, "read back %d bytes",
					bytes->len);
			memcpy(bytes->bytes, r, bytes->len);
		}
	}
	if (bytes->block)
		sst_free_block(sst_drv_ctx, block);
out:
	test_and_clear_bit(pvt_id, &sst_drv_ctx->pvt_id);
	return ret;
}