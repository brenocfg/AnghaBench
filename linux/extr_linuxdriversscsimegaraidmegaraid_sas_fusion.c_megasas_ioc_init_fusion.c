#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int RequestFlags; } ;
struct TYPE_16__ {void* high; void* low; } ;
union MEGASAS_REQUEST_DESCRIPTOR_UNION {TYPE_4__ MFAIo; TYPE_3__ u; } ;
typedef  int u8 ;
typedef  int u32 ;
struct megasas_instance {scalar_t__ adapter_type; int fw_sync_cache_support; scalar_t__ max_chain_frame_sz; TYPE_6__* host; TYPE_8__* pdev; TYPE_7__* reg_set; TYPE_5__* instancet; int /*<<< orphan*/  system_info_h; TYPE_2__* system_info_buf; scalar_t__ consistent_mask_64bit; int /*<<< orphan*/  msix_vectors; scalar_t__ is_rdpq; struct fusion_context* ctrl_context; } ;
struct TYPE_12__ {int /*<<< orphan*/  mfi_capabilities; } ;
struct megasas_init_frame {int cmd_status; void* data_xfer_len; void* queue_info_new_phys_addr_lo; void* queue_info_new_phys_addr_hi; void* system_info_hi; void* system_info_lo; TYPE_10__ driver_operations; int /*<<< orphan*/  cmd; void* TimeStamp; int /*<<< orphan*/  HostPageSize; int /*<<< orphan*/  HostMSIxVectors; void* SenseBufferAddressHigh; void* SystemRequestFrameBaseAddress; int /*<<< orphan*/  MsgFlags; void* ReplyDescriptorPostQueueAddress; void* ReplyDescriptorPostQueueDepth; void* SystemRequestFrameSize; void* HeaderVersion; void* MsgVersion; int /*<<< orphan*/  WhoInit; int /*<<< orphan*/  Function; } ;
struct megasas_header {int cmd_status; void* flags; } ;
struct megasas_cmd {TYPE_9__* frame; int /*<<< orphan*/  frame_phys_addr; } ;
struct fusion_context {int reply_q_depth; int /*<<< orphan*/  sense_phys_addr; int /*<<< orphan*/  io_request_frames_phys; int /*<<< orphan*/ * reply_frames_desc_phys; int /*<<< orphan*/  rdpq_phys; struct megasas_cmd* ioc_init_cmd; struct megasas_init_frame* ioc_init_request; int /*<<< orphan*/  ioc_init_request_phys; } ;
struct MPI2_IOC_INIT_REQUEST {int cmd_status; void* data_xfer_len; void* queue_info_new_phys_addr_lo; void* queue_info_new_phys_addr_hi; void* system_info_hi; void* system_info_lo; TYPE_10__ driver_operations; int /*<<< orphan*/  cmd; void* TimeStamp; int /*<<< orphan*/  HostPageSize; int /*<<< orphan*/  HostMSIxVectors; void* SenseBufferAddressHigh; void* SystemRequestFrameBaseAddress; int /*<<< orphan*/  MsgFlags; void* ReplyDescriptorPostQueueAddress; void* ReplyDescriptorPostQueueDepth; void* SystemRequestFrameSize; void* HeaderVersion; void* MsgVersion; int /*<<< orphan*/  WhoInit; int /*<<< orphan*/  Function; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_22__ {struct megasas_header hdr; } ;
struct TYPE_21__ {int /*<<< orphan*/  dev; } ;
struct TYPE_20__ {int /*<<< orphan*/  doorbell; int /*<<< orphan*/  outbound_scratch_pad_2; } ;
struct TYPE_19__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* disable_intr ) (struct megasas_instance*) ;} ;
struct TYPE_15__ {int systemIdLength; int /*<<< orphan*/  systemId; } ;
struct TYPE_14__ {int support_additional_msix; int support_fp_remote_lun; int support_max_255lds; int support_ndrive_r1_lb; int security_protocol_cmds_fw; int support_ext_io_size; int support_fp_rlbypass; int support_ext_queue_depth; int support_qd_throttling; int support_pd_map_target_id; int support_nvme_passthru; int support_64bit_mode; } ;
struct TYPE_13__ {TYPE_1__ mfi_capabilities; } ;
typedef  TYPE_11__ MFI_CAPABILITIES ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_PRODUCT_UUID ; 
 scalar_t__ INVADER_SERIES ; 
 int IOC_INIT_FRAME_SIZE ; 
 scalar_t__ MEGASAS_CHAIN_FRAME_SZ_MIN ; 
 int MEGASAS_REQ_DESCRIPT_FLAGS_MFA ; 
 int MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT ; 
 int MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE ; 
 int /*<<< orphan*/  MFI_CMD_INIT ; 
 int MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 int /*<<< orphan*/  MFI_POLL_TIMEOUT_SECS ; 
 int /*<<< orphan*/  MPI2_FUNCTION_IOC_INIT ; 
 int MPI2_HEADER_VERSION ; 
 int /*<<< orphan*/  MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE ; 
 int MPI2_VERSION ; 
 int /*<<< orphan*/  MPI2_WHOINIT_HOST_DRIVER ; 
 int MR_CAN_HANDLE_64_BIT_DMA_OFFSET ; 
 int MR_CAN_HANDLE_SYNC_CACHE_OFFSET ; 
 int /*<<< orphan*/  MR_DEFAULT_NVME_PAGE_SHIFT ; 
 int MR_RDPQ_MODE_OFFSET ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dual_qdepth_disable ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ms (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megaraid_sas_kill_hba (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_fire_cmd_fusion (struct megasas_instance*,union MEGASAS_REQUEST_DESCRIPTOR_UNION*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct megasas_init_frame*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_and_poll (struct megasas_instance*,struct megasas_cmd*,int /*<<< orphan*/ ) ; 

int
megasas_ioc_init_fusion(struct megasas_instance *instance)
{
	struct megasas_init_frame *init_frame;
	struct MPI2_IOC_INIT_REQUEST *IOCInitMessage = NULL;
	dma_addr_t	ioc_init_handle;
	struct megasas_cmd *cmd;
	u8 ret, cur_rdpq_mode;
	struct fusion_context *fusion;
	union MEGASAS_REQUEST_DESCRIPTOR_UNION req_desc;
	int i;
	struct megasas_header *frame_hdr;
	const char *sys_info;
	MFI_CAPABILITIES *drv_ops;
	u32 scratch_pad_2;
	ktime_t time;
	bool cur_fw_64bit_dma_capable;

	fusion = instance->ctrl_context;

	ioc_init_handle = fusion->ioc_init_request_phys;
	IOCInitMessage = fusion->ioc_init_request;

	cmd = fusion->ioc_init_cmd;

	scratch_pad_2 = readl
		(&instance->reg_set->outbound_scratch_pad_2);

	cur_rdpq_mode = (scratch_pad_2 & MR_RDPQ_MODE_OFFSET) ? 1 : 0;

	if (instance->adapter_type == INVADER_SERIES) {
		cur_fw_64bit_dma_capable =
			(scratch_pad_2 & MR_CAN_HANDLE_64_BIT_DMA_OFFSET) ? true : false;

		if (instance->consistent_mask_64bit && !cur_fw_64bit_dma_capable) {
			dev_err(&instance->pdev->dev, "Driver was operating on 64bit "
				"DMA mask, but upcoming FW does not support 64bit DMA mask\n");
			megaraid_sas_kill_hba(instance);
			ret = 1;
			goto fail_fw_init;
		}
	}

	if (instance->is_rdpq && !cur_rdpq_mode) {
		dev_err(&instance->pdev->dev, "Firmware downgrade *NOT SUPPORTED*"
			" from RDPQ mode to non RDPQ mode\n");
		ret = 1;
		goto fail_fw_init;
	}

	instance->fw_sync_cache_support = (scratch_pad_2 &
		MR_CAN_HANDLE_SYNC_CACHE_OFFSET) ? 1 : 0;
	dev_info(&instance->pdev->dev, "FW supports sync cache\t: %s\n",
		 instance->fw_sync_cache_support ? "Yes" : "No");

	memset(IOCInitMessage, 0, sizeof(struct MPI2_IOC_INIT_REQUEST));

	IOCInitMessage->Function = MPI2_FUNCTION_IOC_INIT;
	IOCInitMessage->WhoInit	= MPI2_WHOINIT_HOST_DRIVER;
	IOCInitMessage->MsgVersion = cpu_to_le16(MPI2_VERSION);
	IOCInitMessage->HeaderVersion = cpu_to_le16(MPI2_HEADER_VERSION);
	IOCInitMessage->SystemRequestFrameSize = cpu_to_le16(MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE / 4);

	IOCInitMessage->ReplyDescriptorPostQueueDepth = cpu_to_le16(fusion->reply_q_depth);
	IOCInitMessage->ReplyDescriptorPostQueueAddress = instance->is_rdpq ?
			cpu_to_le64(fusion->rdpq_phys) :
			cpu_to_le64(fusion->reply_frames_desc_phys[0]);
	IOCInitMessage->MsgFlags = instance->is_rdpq ?
			MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE : 0;
	IOCInitMessage->SystemRequestFrameBaseAddress = cpu_to_le64(fusion->io_request_frames_phys);
	IOCInitMessage->SenseBufferAddressHigh = cpu_to_le32(upper_32_bits(fusion->sense_phys_addr));
	IOCInitMessage->HostMSIxVectors = instance->msix_vectors;
	IOCInitMessage->HostPageSize = MR_DEFAULT_NVME_PAGE_SHIFT;

	time = ktime_get_real();
	/* Convert to milliseconds as per FW requirement */
	IOCInitMessage->TimeStamp = cpu_to_le64(ktime_to_ms(time));

	init_frame = (struct megasas_init_frame *)cmd->frame;
	memset(init_frame, 0, IOC_INIT_FRAME_SIZE);

	frame_hdr = &cmd->frame->hdr;
	frame_hdr->cmd_status = 0xFF;
	frame_hdr->flags = cpu_to_le16(
		le16_to_cpu(frame_hdr->flags) |
		MFI_FRAME_DONT_POST_IN_REPLY_QUEUE);

	init_frame->cmd	= MFI_CMD_INIT;
	init_frame->cmd_status = 0xFF;

	drv_ops = (MFI_CAPABILITIES *) &(init_frame->driver_operations);

	/* driver support Extended MSIX */
	if (instance->adapter_type >= INVADER_SERIES)
		drv_ops->mfi_capabilities.support_additional_msix = 1;
	/* driver supports HA / Remote LUN over Fast Path interface */
	drv_ops->mfi_capabilities.support_fp_remote_lun = 1;

	drv_ops->mfi_capabilities.support_max_255lds = 1;
	drv_ops->mfi_capabilities.support_ndrive_r1_lb = 1;
	drv_ops->mfi_capabilities.security_protocol_cmds_fw = 1;

	if (instance->max_chain_frame_sz > MEGASAS_CHAIN_FRAME_SZ_MIN)
		drv_ops->mfi_capabilities.support_ext_io_size = 1;

	drv_ops->mfi_capabilities.support_fp_rlbypass = 1;
	if (!dual_qdepth_disable)
		drv_ops->mfi_capabilities.support_ext_queue_depth = 1;

	drv_ops->mfi_capabilities.support_qd_throttling = 1;
	drv_ops->mfi_capabilities.support_pd_map_target_id = 1;
	drv_ops->mfi_capabilities.support_nvme_passthru = 1;

	if (instance->consistent_mask_64bit)
		drv_ops->mfi_capabilities.support_64bit_mode = 1;

	/* Convert capability to LE32 */
	cpu_to_le32s((u32 *)&init_frame->driver_operations.mfi_capabilities);

	sys_info = dmi_get_system_info(DMI_PRODUCT_UUID);
	if (instance->system_info_buf && sys_info) {
		memcpy(instance->system_info_buf->systemId, sys_info,
			strlen(sys_info) > 64 ? 64 : strlen(sys_info));
		instance->system_info_buf->systemIdLength =
			strlen(sys_info) > 64 ? 64 : strlen(sys_info);
		init_frame->system_info_lo = cpu_to_le32(lower_32_bits(instance->system_info_h));
		init_frame->system_info_hi = cpu_to_le32(upper_32_bits(instance->system_info_h));
	}

	init_frame->queue_info_new_phys_addr_hi =
		cpu_to_le32(upper_32_bits(ioc_init_handle));
	init_frame->queue_info_new_phys_addr_lo =
		cpu_to_le32(lower_32_bits(ioc_init_handle));
	init_frame->data_xfer_len = cpu_to_le32(sizeof(struct MPI2_IOC_INIT_REQUEST));

	req_desc.u.low = cpu_to_le32(lower_32_bits(cmd->frame_phys_addr));
	req_desc.u.high = cpu_to_le32(upper_32_bits(cmd->frame_phys_addr));
	req_desc.MFAIo.RequestFlags =
		(MEGASAS_REQ_DESCRIPT_FLAGS_MFA <<
		MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);

	/*
	 * disable the intr before firing the init frame
	 */
	instance->instancet->disable_intr(instance);

	for (i = 0; i < (10 * 1000); i += 20) {
		if (readl(&instance->reg_set->doorbell) & 1)
			msleep(20);
		else
			break;
	}

	megasas_fire_cmd_fusion(instance, &req_desc);

	wait_and_poll(instance, cmd, MFI_POLL_TIMEOUT_SECS);

	frame_hdr = &cmd->frame->hdr;
	if (frame_hdr->cmd_status != 0) {
		ret = 1;
		goto fail_fw_init;
	}

	return 0;

fail_fw_init:
	dev_err(&instance->pdev->dev,
		"Init cmd return status FAILED for SCSI host %d\n",
		instance->host->host_no);

	return ret;
}