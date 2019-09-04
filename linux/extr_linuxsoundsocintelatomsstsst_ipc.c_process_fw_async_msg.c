#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stream_info {int /*<<< orphan*/  drain_cb_param; int /*<<< orphan*/  (* drain_notify ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  compr_cb_param; int /*<<< orphan*/  (* compr_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pcm_substream; int /*<<< orphan*/  (* period_elapsed ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int header_low_payload; } ;
struct TYPE_4__ {TYPE_1__ p; } ;
struct ipc_post {void* mailbox_data; TYPE_2__ mrfld_header; } ;
struct ipc_dsp_hdr {int cmd_id; int pipe_id; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; struct stream_info* streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
#define  IPC_IA_BUF_UNDER_RUN_MRFLD 132 
#define  IPC_IA_DRAIN_STREAM_MRFLD 131 
#define  IPC_IA_FW_ASYNC_ERR_MRFLD 130 
#define  IPC_IA_FW_INIT_CMPLT_MRFLD 129 
#define  IPC_SST_PERIOD_ELAPSED_MRFLD 128 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  STREAM_INIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int get_stream_id_mrfld (struct intel_sst_drv*,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,void*,int,int) ; 
 int /*<<< orphan*/  process_fw_init (struct intel_sst_drv*,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_fw_async_msg(struct intel_sst_drv *sst_drv_ctx,
			struct ipc_post *msg)
{
	u32 msg_id;
	int str_id;
	u32 data_size, i;
	void *data_offset;
	struct stream_info *stream;
	u32 msg_low, pipe_id;

	msg_low = msg->mrfld_header.p.header_low_payload;
	msg_id = ((struct ipc_dsp_hdr *)msg->mailbox_data)->cmd_id;
	data_offset = (msg->mailbox_data + sizeof(struct ipc_dsp_hdr));
	data_size =  msg_low - (sizeof(struct ipc_dsp_hdr));

	switch (msg_id) {
	case IPC_SST_PERIOD_ELAPSED_MRFLD:
		pipe_id = ((struct ipc_dsp_hdr *)msg->mailbox_data)->pipe_id;
		str_id = get_stream_id_mrfld(sst_drv_ctx, pipe_id);
		if (str_id > 0) {
			dev_dbg(sst_drv_ctx->dev,
				"Period elapsed rcvd for pipe id 0x%x\n",
				pipe_id);
			stream = &sst_drv_ctx->streams[str_id];
			/* If stream is dropped, skip processing this message*/
			if (stream->status == STREAM_INIT)
				break;
			if (stream->period_elapsed)
				stream->period_elapsed(stream->pcm_substream);
			if (stream->compr_cb)
				stream->compr_cb(stream->compr_cb_param);
		}
		break;

	case IPC_IA_DRAIN_STREAM_MRFLD:
		pipe_id = ((struct ipc_dsp_hdr *)msg->mailbox_data)->pipe_id;
		str_id = get_stream_id_mrfld(sst_drv_ctx, pipe_id);
		if (str_id > 0) {
			stream = &sst_drv_ctx->streams[str_id];
			if (stream->drain_notify)
				stream->drain_notify(stream->drain_cb_param);
		}
		break;

	case IPC_IA_FW_ASYNC_ERR_MRFLD:
		dev_err(sst_drv_ctx->dev, "FW sent async error msg:\n");
		for (i = 0; i < (data_size/4); i++)
			print_hex_dump(KERN_DEBUG, NULL, DUMP_PREFIX_NONE,
					16, 4, data_offset, data_size, false);
		break;

	case IPC_IA_FW_INIT_CMPLT_MRFLD:
		process_fw_init(sst_drv_ctx, data_offset);
		break;

	case IPC_IA_BUF_UNDER_RUN_MRFLD:
		pipe_id = ((struct ipc_dsp_hdr *)msg->mailbox_data)->pipe_id;
		str_id = get_stream_id_mrfld(sst_drv_ctx, pipe_id);
		if (str_id > 0)
			dev_err(sst_drv_ctx->dev,
				"Buffer under-run for pipe:%#x str_id:%d\n",
				pipe_id, str_id);
		break;

	default:
		dev_err(sst_drv_ctx->dev,
			"Unrecognized async msg from FW msg_id %#x\n", msg_id);
	}
}