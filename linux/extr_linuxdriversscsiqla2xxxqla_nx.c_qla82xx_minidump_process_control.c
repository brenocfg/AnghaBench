#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qla_hw_data {scalar_t__ md_tmplt_hdr; } ;
struct qla82xx_md_template_hdr {int* saved_state_array; } ;
struct TYPE_6__ {int poll_timeout; int state_index_a; scalar_t__ addr_stride; } ;
struct TYPE_5__ {int opcode; int state_index_v; int shl; int shr; } ;
struct qla82xx_md_entry_crb {int addr; int op_count; int value_1; int value_2; int value_3; TYPE_2__ crb_strd; TYPE_1__ crb_ctrl; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 int QLA82XX_DBG_OPCODE_AND ; 
 int QLA82XX_DBG_OPCODE_MDSTATE ; 
 int QLA82XX_DBG_OPCODE_OR ; 
 int QLA82XX_DBG_OPCODE_POLL ; 
 int QLA82XX_DBG_OPCODE_RDSTATE ; 
 int QLA82XX_DBG_OPCODE_RW ; 
 int QLA82XX_DBG_OPCODE_WR ; 
 int QLA82XX_DBG_OPCODE_WRSTATE ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int jiffies ; 
 int qla82xx_md_rw_32 (struct qla_hw_data*,int,int,int) ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 

__attribute__((used)) static int
qla82xx_minidump_process_control(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	struct qla82xx_md_entry_crb *crb_entry;
	uint32_t read_value, opcode, poll_time;
	uint32_t addr, index, crb_addr;
	unsigned long wtime;
	struct qla82xx_md_template_hdr *tmplt_hdr;
	uint32_t rval = QLA_SUCCESS;
	int i;

	tmplt_hdr = (struct qla82xx_md_template_hdr *)ha->md_tmplt_hdr;
	crb_entry = (struct qla82xx_md_entry_crb *)entry_hdr;
	crb_addr = crb_entry->addr;

	for (i = 0; i < crb_entry->op_count; i++) {
		opcode = crb_entry->crb_ctrl.opcode;
		if (opcode & QLA82XX_DBG_OPCODE_WR) {
			qla82xx_md_rw_32(ha, crb_addr,
			    crb_entry->value_1, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_WR;
		}

		if (opcode & QLA82XX_DBG_OPCODE_RW) {
			read_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);
			qla82xx_md_rw_32(ha, crb_addr, read_value, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_RW;
		}

		if (opcode & QLA82XX_DBG_OPCODE_AND) {
			read_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);
			read_value &= crb_entry->value_2;
			opcode &= ~QLA82XX_DBG_OPCODE_AND;
			if (opcode & QLA82XX_DBG_OPCODE_OR) {
				read_value |= crb_entry->value_3;
				opcode &= ~QLA82XX_DBG_OPCODE_OR;
			}
			qla82xx_md_rw_32(ha, crb_addr, read_value, 1);
		}

		if (opcode & QLA82XX_DBG_OPCODE_OR) {
			read_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);
			read_value |= crb_entry->value_3;
			qla82xx_md_rw_32(ha, crb_addr, read_value, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_OR;
		}

		if (opcode & QLA82XX_DBG_OPCODE_POLL) {
			poll_time = crb_entry->crb_strd.poll_timeout;
			wtime = jiffies + poll_time;
			read_value = qla82xx_md_rw_32(ha, crb_addr, 0, 0);

			do {
				if ((read_value & crb_entry->value_2)
				    == crb_entry->value_1)
					break;
				else if (time_after_eq(jiffies, wtime)) {
					/* capturing dump failed */
					rval = QLA_FUNCTION_FAILED;
					break;
				} else
					read_value = qla82xx_md_rw_32(ha,
					    crb_addr, 0, 0);
			} while (1);
			opcode &= ~QLA82XX_DBG_OPCODE_POLL;
		}

		if (opcode & QLA82XX_DBG_OPCODE_RDSTATE) {
			if (crb_entry->crb_strd.state_index_a) {
				index = crb_entry->crb_strd.state_index_a;
				addr = tmplt_hdr->saved_state_array[index];
			} else
				addr = crb_addr;

			read_value = qla82xx_md_rw_32(ha, addr, 0, 0);
			index = crb_entry->crb_ctrl.state_index_v;
			tmplt_hdr->saved_state_array[index] = read_value;
			opcode &= ~QLA82XX_DBG_OPCODE_RDSTATE;
		}

		if (opcode & QLA82XX_DBG_OPCODE_WRSTATE) {
			if (crb_entry->crb_strd.state_index_a) {
				index = crb_entry->crb_strd.state_index_a;
				addr = tmplt_hdr->saved_state_array[index];
			} else
				addr = crb_addr;

			if (crb_entry->crb_ctrl.state_index_v) {
				index = crb_entry->crb_ctrl.state_index_v;
				read_value =
				    tmplt_hdr->saved_state_array[index];
			} else
				read_value = crb_entry->value_1;

			qla82xx_md_rw_32(ha, addr, read_value, 1);
			opcode &= ~QLA82XX_DBG_OPCODE_WRSTATE;
		}

		if (opcode & QLA82XX_DBG_OPCODE_MDSTATE) {
			index = crb_entry->crb_ctrl.state_index_v;
			read_value = tmplt_hdr->saved_state_array[index];
			read_value <<= crb_entry->crb_ctrl.shl;
			read_value >>= crb_entry->crb_ctrl.shr;
			if (crb_entry->value_2)
				read_value &= crb_entry->value_2;
			read_value |= crb_entry->value_3;
			read_value += crb_entry->value_1;
			tmplt_hdr->saved_state_array[index] = read_value;
			opcode &= ~QLA82XX_DBG_OPCODE_MDSTATE;
		}
		crb_addr += crb_entry->crb_strd.addr_stride;
	}
	return rval;
}