#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct iscsi_task_params {int /*<<< orphan*/  conn_icid; int /*<<< orphan*/  cq_rss_number; struct e4_iscsi_task_context* context; } ;
struct TYPE_14__ {void* icid; int /*<<< orphan*/  flags1; } ;
struct TYPE_13__ {int task_type; int /*<<< orphan*/  cq_rss_number; } ;
struct TYPE_12__ {void* task_cid; int /*<<< orphan*/  cdu_validation; } ;
struct TYPE_11__ {int task_type; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
struct TYPE_10__ {TYPE_2__ pdu_hdr; } ;
struct e4_iscsi_task_context {TYPE_7__ ustorm_ag_context; TYPE_6__ ustorm_st_context; TYPE_5__ mstorm_ag_context; TYPE_4__ mstorm_st_context; TYPE_3__ ystorm_st_context; } ;
struct data_hdr {int /*<<< orphan*/ * data; } ;
typedef  enum iscsi_task_type { ____Placeholder_iscsi_task_type } iscsi_task_type ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E4_USTORM_ISCSI_TASK_AG_CTX_R2T2RECV ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct e4_iscsi_task_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_default_iscsi_task(struct iscsi_task_params *task_params,
				    struct data_hdr *pdu_header,
				    enum iscsi_task_type task_type)
{
	struct e4_iscsi_task_context *context;
	u32 val;
	u16 index;
	u8 val_byte;

	context = task_params->context;
	val_byte = context->mstorm_ag_context.cdu_validation;
	memset(context, 0, sizeof(*context));
	context->mstorm_ag_context.cdu_validation = val_byte;

	for (index = 0; index <
	     ARRAY_SIZE(context->ystorm_st_context.pdu_hdr.data.data);
	     index++) {
		val = cpu_to_le32(pdu_header->data[index]);
		context->ystorm_st_context.pdu_hdr.data.data[index] = val;
	}

	context->mstorm_st_context.task_type = task_type;
	context->mstorm_ag_context.task_cid =
					    cpu_to_le16(task_params->conn_icid);

	SET_FIELD(context->ustorm_ag_context.flags1,
		  E4_USTORM_ISCSI_TASK_AG_CTX_R2T2RECV, 1);

	context->ustorm_st_context.task_type = task_type;
	context->ustorm_st_context.cq_rss_number = task_params->cq_rss_number;
	context->ustorm_ag_context.icid = cpu_to_le16(task_params->conn_icid);
}