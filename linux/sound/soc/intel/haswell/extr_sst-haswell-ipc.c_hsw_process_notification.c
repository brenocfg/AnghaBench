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
typedef  int u32 ;
struct sst_hsw {int /*<<< orphan*/  dev; int /*<<< orphan*/  boot_complete; struct sst_dsp* dsp; } ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int IPC_FW_READY ; 
#define  IPC_GLB_ALLOCATE_STREAM 142 
#define  IPC_GLB_DEBUG_LOG_MESSAGE 141 
#define  IPC_GLB_ENTER_DX_STATE 140 
#define  IPC_GLB_FREE_STREAM 139 
#define  IPC_GLB_GET_DEVICE_FORMATS 138 
#define  IPC_GLB_GET_FW_CAPABILITIES 137 
#define  IPC_GLB_GET_FW_VERSION 136 
#define  IPC_GLB_GET_MIXER_STREAM_INFO 135 
#define  IPC_GLB_MAX_IPC_MESSAGE_TYPE 134 
#define  IPC_GLB_MODULE_OPERATION 133 
#define  IPC_GLB_REQUEST_DUMP 132 
#define  IPC_GLB_RESTORE_CONTEXT 131 
#define  IPC_GLB_SET_DEVICE_FORMATS 130 
#define  IPC_GLB_SHORT_REPLY 129 
#define  IPC_GLB_STREAM_MESSAGE 128 
 int /*<<< orphan*/  SST_IPCD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  hsw_fw_ready (struct sst_hsw*,int) ; 
 int hsw_log_message (struct sst_hsw*,int) ; 
 int hsw_module_message (struct sst_hsw*,int) ; 
 int hsw_stream_message (struct sst_hsw*,int) ; 
 int msg_get_global_type (int) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int) ; 

__attribute__((used)) static int hsw_process_notification(struct sst_hsw *hsw)
{
	struct sst_dsp *sst = hsw->dsp;
	u32 type, header;
	int handled = 1;

	header = sst_dsp_shim_read_unlocked(sst, SST_IPCD);
	type = msg_get_global_type(header);

	trace_ipc_request("processing -->", header);

	/* FW Ready is a special case */
	if (!hsw->boot_complete && header & IPC_FW_READY) {
		hsw_fw_ready(hsw, header);
		return handled;
	}

	switch (type) {
	case IPC_GLB_GET_FW_VERSION:
	case IPC_GLB_ALLOCATE_STREAM:
	case IPC_GLB_FREE_STREAM:
	case IPC_GLB_GET_FW_CAPABILITIES:
	case IPC_GLB_REQUEST_DUMP:
	case IPC_GLB_GET_DEVICE_FORMATS:
	case IPC_GLB_SET_DEVICE_FORMATS:
	case IPC_GLB_ENTER_DX_STATE:
	case IPC_GLB_GET_MIXER_STREAM_INFO:
	case IPC_GLB_MAX_IPC_MESSAGE_TYPE:
	case IPC_GLB_RESTORE_CONTEXT:
	case IPC_GLB_SHORT_REPLY:
		dev_err(hsw->dev, "error: message type %d header 0x%x\n",
			type, header);
		break;
	case IPC_GLB_STREAM_MESSAGE:
		handled = hsw_stream_message(hsw, header);
		break;
	case IPC_GLB_DEBUG_LOG_MESSAGE:
		handled = hsw_log_message(hsw, header);
		break;
	case IPC_GLB_MODULE_OPERATION:
		handled = hsw_module_message(hsw, header);
		break;
	default:
		dev_err(hsw->dev, "error: unexpected type %d hdr 0x%8.8x\n",
			type, header);
		break;
	}

	return handled;
}