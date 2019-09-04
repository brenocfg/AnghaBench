#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct iscsi_session {TYPE_1__* sess_ops; } ;
struct iscsi_seq {int dummy; } ;
struct iscsi_pdu {int dummy; } ;
struct iscsi_node_attrib {scalar_t__ random_r2t_offsets; scalar_t__ random_datain_seq_offsets; scalar_t__ random_datain_pdu_offsets; } ;
struct iscsi_conn {struct iscsi_session* sess; } ;
struct iscsi_cmd {scalar_t__ data_direction; void* pdu_count; struct iscsi_pdu* pdu_list; void* seq_count; struct iscsi_seq* seq_list; scalar_t__ unsolicited_data; scalar_t__ immediate_data; struct iscsi_conn* conn; } ;
struct iscsi_build_list {void* type; int /*<<< orphan*/  randomize; void* immediate_data_length; int /*<<< orphan*/  data_direction; } ;
struct TYPE_2__ {scalar_t__ DataPDUInOrder; scalar_t__ DataSequenceInOrder; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ISCSI_PDU_READ ; 
 int /*<<< orphan*/  ISCSI_PDU_WRITE ; 
 void* PDULIST_IMMEDIATE ; 
 void* PDULIST_IMMEDIATE_AND_UNSOLICITED ; 
 void* PDULIST_NORMAL ; 
 void* PDULIST_UNSOLICITED ; 
 int /*<<< orphan*/  RANDOM_DATAIN_PDU_OFFSETS ; 
 int /*<<< orphan*/  RANDOM_DATAIN_SEQ_OFFSETS ; 
 int /*<<< orphan*/  RANDOM_R2T_OFFSETS ; 
 int /*<<< orphan*/  iscsit_determine_counts_for_list (struct iscsi_cmd*,struct iscsi_build_list*,void**,void**) ; 
 int iscsit_do_build_pdu_and_seq_lists (struct iscsi_cmd*,struct iscsi_build_list*) ; 
 struct iscsi_node_attrib* iscsit_tpg_get_node_attrib (struct iscsi_session*) ; 
 void* kcalloc (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iscsi_seq*) ; 
 int /*<<< orphan*/  memset (struct iscsi_build_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int iscsit_build_pdu_and_seq_lists(
	struct iscsi_cmd *cmd,
	u32 immediate_data_length)
{
	struct iscsi_build_list bl;
	u32 pdu_count = 0, seq_count = 1;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_pdu *pdu = NULL;
	struct iscsi_seq *seq = NULL;

	struct iscsi_session *sess = conn->sess;
	struct iscsi_node_attrib *na;

	/*
	 * Do nothing if no OOO shenanigans
	 */
	if (sess->sess_ops->DataSequenceInOrder &&
	    sess->sess_ops->DataPDUInOrder)
		return 0;

	if (cmd->data_direction == DMA_NONE)
		return 0;

	na = iscsit_tpg_get_node_attrib(sess);
	memset(&bl, 0, sizeof(struct iscsi_build_list));

	if (cmd->data_direction == DMA_FROM_DEVICE) {
		bl.data_direction = ISCSI_PDU_READ;
		bl.type = PDULIST_NORMAL;
		if (na->random_datain_pdu_offsets)
			bl.randomize |= RANDOM_DATAIN_PDU_OFFSETS;
		if (na->random_datain_seq_offsets)
			bl.randomize |= RANDOM_DATAIN_SEQ_OFFSETS;
	} else {
		bl.data_direction = ISCSI_PDU_WRITE;
		bl.immediate_data_length = immediate_data_length;
		if (na->random_r2t_offsets)
			bl.randomize |= RANDOM_R2T_OFFSETS;

		if (!cmd->immediate_data && !cmd->unsolicited_data)
			bl.type = PDULIST_NORMAL;
		else if (cmd->immediate_data && !cmd->unsolicited_data)
			bl.type = PDULIST_IMMEDIATE;
		else if (!cmd->immediate_data && cmd->unsolicited_data)
			bl.type = PDULIST_UNSOLICITED;
		else if (cmd->immediate_data && cmd->unsolicited_data)
			bl.type = PDULIST_IMMEDIATE_AND_UNSOLICITED;
	}

	iscsit_determine_counts_for_list(cmd, &bl, &seq_count, &pdu_count);

	if (!conn->sess->sess_ops->DataSequenceInOrder) {
		seq = kcalloc(seq_count, sizeof(struct iscsi_seq), GFP_ATOMIC);
		if (!seq) {
			pr_err("Unable to allocate struct iscsi_seq list\n");
			return -ENOMEM;
		}
		cmd->seq_list = seq;
		cmd->seq_count = seq_count;
	}

	if (!conn->sess->sess_ops->DataPDUInOrder) {
		pdu = kcalloc(pdu_count, sizeof(struct iscsi_pdu), GFP_ATOMIC);
		if (!pdu) {
			pr_err("Unable to allocate struct iscsi_pdu list.\n");
			kfree(seq);
			return -ENOMEM;
		}
		cmd->pdu_list = pdu;
		cmd->pdu_count = pdu_count;
	}

	return iscsit_do_build_pdu_and_seq_lists(cmd, &bl);
}