#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  void* u32 ;
struct TYPE_12__ {void* sgl_num_sges; } ;
struct TYPE_8__ {int /*<<< orphan*/  fcp_cmd_payload; } ;
struct ystorm_fcoe_task_st_ctx {int expect_first_xfer; int /*<<< orphan*/  data_desc; TYPE_6__ sgl_params; int /*<<< orphan*/  sgl_mode; TYPE_2__ tx_info_union; void* task_type; void* task_rety_identifier; void* data_2_trns_rem; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; void* rx_id; } ;
struct TYPE_9__ {void* task_type; void* fcp_cmd_trns_size; void* glbl_q_num; void* cid; void* dev_type; } ;
struct tstorm_fcoe_task_st_ctx {TYPE_5__ read_write; TYPE_3__ read_only; } ;
struct scsi_sgl_task_params {int /*<<< orphan*/  num_sges; int /*<<< orphan*/  small_mid_sge; } ;
struct regpair {void* hi; void* lo; } ;
struct TYPE_10__ {void* lo; void* hi; } ;
struct mstorm_fcoe_task_st_ctx {int /*<<< orphan*/  data_desc; TYPE_6__ sgl_params; void* data_2_trns_rem; int /*<<< orphan*/  flags; TYPE_4__ rsp_buf_addr; } ;
struct fcoe_task_params {scalar_t__ task_type; int is_tape_device; void* conn_cid; void* cq_rss_number; void* rx_io_size; void* tx_io_size; struct e4_fcoe_task_context* context; } ;
struct fcoe_fcp_cmd_payload {int dummy; } ;
struct e4_ustorm_fcoe_task_ag_ctx {void* global_cq_num; } ;
struct TYPE_7__ {void* byte0; } ;
struct e4_fcoe_task_context {struct mstorm_fcoe_task_st_ctx mstorm_st_context; struct e4_ustorm_fcoe_task_ag_ctx ustorm_ag_context; struct tstorm_fcoe_task_st_ctx tstorm_st_context; struct ystorm_fcoe_task_st_ctx ystorm_st_context; TYPE_1__ ystorm_ag_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_RX_ID ; 
 scalar_t__ FCOE_TASK_DEV_TYPE_DISK ; 
 scalar_t__ FCOE_TASK_DEV_TYPE_TAPE ; 
 scalar_t__ FCOE_TASK_TYPE_WRITE_INITIATOR ; 
 int /*<<< orphan*/  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME ; 
 int /*<<< orphan*/  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RX_SGL_MODE ; 
 int /*<<< orphan*/  MSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE ; 
 int SCSI_FAST_SGL ; 
 int SCSI_TX_SLOW_SGL ; 
 int /*<<< orphan*/  SEND_FCOE_CMD ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (void*) ; 
 int /*<<< orphan*/  init_common_sqe (struct fcoe_task_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_scsi_sgl_context (TYPE_6__*,int /*<<< orphan*/ *,struct scsi_sgl_task_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  memset (struct e4_fcoe_task_context*,int /*<<< orphan*/ ,int) ; 
 int scsi_is_slow_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int init_initiator_rw_fcoe_task(struct fcoe_task_params *task_params,
				struct scsi_sgl_task_params *sgl_task_params,
				struct regpair sense_data_buffer_phys_addr,
				u32 task_retry_id,
				u8 fcp_cmd_payload[32])
{
	struct e4_fcoe_task_context *ctx = task_params->context;
	const u8 val_byte = ctx->ystorm_ag_context.byte0;
	struct e4_ustorm_fcoe_task_ag_ctx *u_ag_ctx;
	struct ystorm_fcoe_task_st_ctx *y_st_ctx;
	struct tstorm_fcoe_task_st_ctx *t_st_ctx;
	struct mstorm_fcoe_task_st_ctx *m_st_ctx;
	u32 io_size, val;
	bool slow_sgl;

	memset(ctx, 0, sizeof(*(ctx)));
	ctx->ystorm_ag_context.byte0 = val_byte;
	slow_sgl = scsi_is_slow_sgl(sgl_task_params->num_sges,
				    sgl_task_params->small_mid_sge);
	io_size = (task_params->task_type == FCOE_TASK_TYPE_WRITE_INITIATOR ?
		   task_params->tx_io_size : task_params->rx_io_size);

	/* Ystorm ctx */
	y_st_ctx = &ctx->ystorm_st_context;
	y_st_ctx->data_2_trns_rem = cpu_to_le32(io_size);
	y_st_ctx->task_rety_identifier = cpu_to_le32(task_retry_id);
	y_st_ctx->task_type = (u8)task_params->task_type;
	memcpy(&y_st_ctx->tx_info_union.fcp_cmd_payload,
	       fcp_cmd_payload, sizeof(struct fcoe_fcp_cmd_payload));

	/* Tstorm ctx */
	t_st_ctx = &ctx->tstorm_st_context;
	t_st_ctx->read_only.dev_type = (u8)(task_params->is_tape_device == 1 ?
					    FCOE_TASK_DEV_TYPE_TAPE :
					    FCOE_TASK_DEV_TYPE_DISK);
	t_st_ctx->read_only.cid = cpu_to_le32(task_params->conn_cid);
	val = cpu_to_le32(task_params->cq_rss_number);
	t_st_ctx->read_only.glbl_q_num = val;
	t_st_ctx->read_only.fcp_cmd_trns_size = cpu_to_le32(io_size);
	t_st_ctx->read_only.task_type = (u8)task_params->task_type;
	SET_FIELD(t_st_ctx->read_write.flags,
		  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME, 1);
	t_st_ctx->read_write.rx_id = cpu_to_le16(FCOE_RX_ID);

	/* Ustorm ctx */
	u_ag_ctx = &ctx->ustorm_ag_context;
	u_ag_ctx->global_cq_num = cpu_to_le32(task_params->cq_rss_number);

	/* Mstorm buffer for sense/rsp data placement */
	m_st_ctx = &ctx->mstorm_st_context;
	val = cpu_to_le32(sense_data_buffer_phys_addr.hi);
	m_st_ctx->rsp_buf_addr.hi = val;
	val = cpu_to_le32(sense_data_buffer_phys_addr.lo);
	m_st_ctx->rsp_buf_addr.lo = val;

	if (task_params->task_type == FCOE_TASK_TYPE_WRITE_INITIATOR) {
		/* Ystorm ctx */
		y_st_ctx->expect_first_xfer = 1;

		/* Set the amount of super SGEs. Can be up to 4. */
		SET_FIELD(y_st_ctx->sgl_mode,
			  YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE,
			  (slow_sgl ? SCSI_TX_SLOW_SGL : SCSI_FAST_SGL));
		init_scsi_sgl_context(&y_st_ctx->sgl_params,
				      &y_st_ctx->data_desc,
				      sgl_task_params);

		/* Mstorm ctx */
		SET_FIELD(m_st_ctx->flags,
			  MSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE,
			  (slow_sgl ? SCSI_TX_SLOW_SGL : SCSI_FAST_SGL));
		m_st_ctx->sgl_params.sgl_num_sges =
			cpu_to_le16(sgl_task_params->num_sges);
	} else {
		/* Tstorm ctx */
		SET_FIELD(t_st_ctx->read_write.flags,
			  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RX_SGL_MODE,
			  (slow_sgl ? SCSI_TX_SLOW_SGL : SCSI_FAST_SGL));

		/* Mstorm ctx */
		m_st_ctx->data_2_trns_rem = cpu_to_le32(io_size);
		init_scsi_sgl_context(&m_st_ctx->sgl_params,
				      &m_st_ctx->data_desc,
				      sgl_task_params);
	}

	/* Init Sqe */
	init_common_sqe(task_params, SEND_FCOE_CMD);

	return 0;
}