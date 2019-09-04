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
typedef  scalar_t__ u32 ;
struct iscsi_conn {TYPE_4__* sess; TYPE_1__* conn_ops; } ;
struct TYPE_6__ {scalar_t__ data_direction; scalar_t__ data_length; } ;
struct iscsi_cmd {TYPE_2__ se_cmd; struct iscsi_conn* conn; } ;
struct iscsi_build_list {scalar_t__ type; scalar_t__ immediate_data_length; } ;
struct TYPE_8__ {TYPE_3__* sess_ops; } ;
struct TYPE_7__ {scalar_t__ FirstBurstLength; scalar_t__ MaxBurstLength; } ;
struct TYPE_5__ {scalar_t__ MaxXmitDataSegmentLength; scalar_t__ MaxRecvDataSegmentLength; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 scalar_t__ PDULIST_IMMEDIATE ; 
 scalar_t__ PDULIST_IMMEDIATE_AND_UNSOLICITED ; 
 scalar_t__ PDULIST_UNSOLICITED ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void iscsit_determine_counts_for_list(
	struct iscsi_cmd *cmd,
	struct iscsi_build_list *bl,
	u32 *seq_count,
	u32 *pdu_count)
{
	int check_immediate = 0;
	u32 burstlength = 0, offset = 0;
	u32 unsolicited_data_length = 0;
	u32 mdsl;
	struct iscsi_conn *conn = cmd->conn;

	if (cmd->se_cmd.data_direction == DMA_TO_DEVICE)
		mdsl = cmd->conn->conn_ops->MaxXmitDataSegmentLength;
	else
		mdsl = cmd->conn->conn_ops->MaxRecvDataSegmentLength;

	if ((bl->type == PDULIST_IMMEDIATE) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		check_immediate = 1;

	if ((bl->type == PDULIST_UNSOLICITED) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		unsolicited_data_length = min(cmd->se_cmd.data_length,
			conn->sess->sess_ops->FirstBurstLength);

	while (offset < cmd->se_cmd.data_length) {
		*pdu_count += 1;

		if (check_immediate) {
			check_immediate = 0;
			offset += bl->immediate_data_length;
			*seq_count += 1;
			if (unsolicited_data_length)
				unsolicited_data_length -=
					bl->immediate_data_length;
			continue;
		}
		if (unsolicited_data_length > 0) {
			if ((offset + mdsl) >= cmd->se_cmd.data_length) {
				unsolicited_data_length -=
					(cmd->se_cmd.data_length - offset);
				offset += (cmd->se_cmd.data_length - offset);
				continue;
			}
			if ((offset + mdsl)
					>= conn->sess->sess_ops->FirstBurstLength) {
				unsolicited_data_length -=
					(conn->sess->sess_ops->FirstBurstLength -
					offset);
				offset += (conn->sess->sess_ops->FirstBurstLength -
					offset);
				burstlength = 0;
				*seq_count += 1;
				continue;
			}

			offset += mdsl;
			unsolicited_data_length -= mdsl;
			continue;
		}
		if ((offset + mdsl) >= cmd->se_cmd.data_length) {
			offset += (cmd->se_cmd.data_length - offset);
			continue;
		}
		if ((burstlength + mdsl) >=
		     conn->sess->sess_ops->MaxBurstLength) {
			offset += (conn->sess->sess_ops->MaxBurstLength -
					burstlength);
			burstlength = 0;
			*seq_count += 1;
			continue;
		}

		burstlength += mdsl;
		offset += mdsl;
	}
}