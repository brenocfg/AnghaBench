#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
typedef  scalar_t__ uchar ;
struct TYPE_13__ {int queue_full_or_busy; scalar_t__* max_dvc_qng; scalar_t__ cur_total_qng; scalar_t__* cur_dvc_qng; int unit_not_ready; int start_motor; int /*<<< orphan*/  max_dma_count; int /*<<< orphan*/  iop_base; } ;
struct TYPE_11__ {scalar_t__ done_stat; scalar_t__ host_stat; } ;
struct TYPE_10__ {unsigned long srb_tag; scalar_t__ target_ix; } ;
struct TYPE_12__ {scalar_t__ q_status; int cntl; scalar_t__ extra_bytes; TYPE_2__ d3; int /*<<< orphan*/  remain_bytes; TYPE_1__ d2; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;
typedef  TYPE_3__ ASC_QDONE_INFO ;
typedef  TYPE_4__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_ERR_CUR_QNG ; 
 int /*<<< orphan*/  ASCQ_ERR_Q_STATUS ; 
 int /*<<< orphan*/  ASCQ_ERR_SG_Q_LINKS ; 
 scalar_t__ ASCV_SCSIBUSY_B ; 
 scalar_t__ ASC_QADR_BEG ; 
 scalar_t__ ASC_QLINK_END ; 
 scalar_t__ ASC_QNO_TO_QADDR (scalar_t__) ; 
 scalar_t__ ASC_SCSIQ_B_FWD ; 
 scalar_t__ ASC_SCSIQ_B_STATUS ; 
 scalar_t__ ASC_SCSIQ_CDB_BEG ; 
 int ASC_TIX_TO_TARGET_ID (scalar_t__) ; 
 scalar_t__ ASC_TIX_TO_TID (scalar_t__) ; 
 scalar_t__ AscGetVarDoneQTail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscPutVarDoneQTail (int /*<<< orphan*/ ,scalar_t__) ; 
 void* AscReadLramByte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AscSetChipControl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AscSetChipStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetLibErrorCode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscStopChip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ CC_HALT ; 
 scalar_t__ CC_SCSI_RESET ; 
 int /*<<< orphan*/  CIW_CLR_SCSI_RESET_INT ; 
 int QC_DATA_IN ; 
 int QC_DATA_OUT ; 
 int QC_NO_CALLBACK ; 
 int QC_SG_HEAD ; 
 scalar_t__ QD_NO_ERROR ; 
 scalar_t__ QD_WITH_ERROR ; 
 scalar_t__ QHSTA_D_QDONE_SG_LIST_CORRUPTED ; 
 scalar_t__ QHSTA_M_DATA_OVER_RUN ; 
 scalar_t__ QHSTA_M_HUNG_REQ_SCSI_BUS_RESET ; 
 void* QHSTA_NO_ERROR ; 
 int QS_ABORTED ; 
 int QS_DONE ; 
 int QS_FREE ; 
 int QS_READY ; 
 void* START_STOP ; 
 scalar_t__ _AscCopyLramScsiDoneQ (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asc_isr_callback (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int AscIsrQDone(ASC_DVC_VAR *asc_dvc)
{
	uchar next_qp;
	uchar n_q_used;
	uchar sg_list_qp;
	uchar sg_queue_cnt;
	uchar q_cnt;
	uchar done_q_tail;
	uchar tid_no;
	ASC_SCSI_BIT_ID_TYPE scsi_busy;
	ASC_SCSI_BIT_ID_TYPE target_id;
	PortAddr iop_base;
	ushort q_addr;
	ushort sg_q_addr;
	uchar cur_target_qng;
	ASC_QDONE_INFO scsiq_buf;
	ASC_QDONE_INFO *scsiq;
	bool false_overrun;

	iop_base = asc_dvc->iop_base;
	n_q_used = 1;
	scsiq = (ASC_QDONE_INFO *)&scsiq_buf;
	done_q_tail = (uchar)AscGetVarDoneQTail(iop_base);
	q_addr = ASC_QNO_TO_QADDR(done_q_tail);
	next_qp = AscReadLramByte(iop_base,
				  (ushort)(q_addr + (ushort)ASC_SCSIQ_B_FWD));
	if (next_qp != ASC_QLINK_END) {
		AscPutVarDoneQTail(iop_base, next_qp);
		q_addr = ASC_QNO_TO_QADDR(next_qp);
		sg_queue_cnt = _AscCopyLramScsiDoneQ(iop_base, q_addr, scsiq,
						     asc_dvc->max_dma_count);
		AscWriteLramByte(iop_base,
				 (ushort)(q_addr +
					  (ushort)ASC_SCSIQ_B_STATUS),
				 (uchar)(scsiq->
					 q_status & (uchar)~(QS_READY |
							     QS_ABORTED)));
		tid_no = ASC_TIX_TO_TID(scsiq->d2.target_ix);
		target_id = ASC_TIX_TO_TARGET_ID(scsiq->d2.target_ix);
		if ((scsiq->cntl & QC_SG_HEAD) != 0) {
			sg_q_addr = q_addr;
			sg_list_qp = next_qp;
			for (q_cnt = 0; q_cnt < sg_queue_cnt; q_cnt++) {
				sg_list_qp = AscReadLramByte(iop_base,
							     (ushort)(sg_q_addr
								      + (ushort)
								      ASC_SCSIQ_B_FWD));
				sg_q_addr = ASC_QNO_TO_QADDR(sg_list_qp);
				if (sg_list_qp == ASC_QLINK_END) {
					AscSetLibErrorCode(asc_dvc,
							   ASCQ_ERR_SG_Q_LINKS);
					scsiq->d3.done_stat = QD_WITH_ERROR;
					scsiq->d3.host_stat =
					    QHSTA_D_QDONE_SG_LIST_CORRUPTED;
					goto FATAL_ERR_QDONE;
				}
				AscWriteLramByte(iop_base,
						 (ushort)(sg_q_addr + (ushort)
							  ASC_SCSIQ_B_STATUS),
						 QS_FREE);
			}
			n_q_used = sg_queue_cnt + 1;
			AscPutVarDoneQTail(iop_base, sg_list_qp);
		}
		if (asc_dvc->queue_full_or_busy & target_id) {
			cur_target_qng = AscReadLramByte(iop_base,
							 (ushort)((ushort)
								  ASC_QADR_BEG
								  + (ushort)
								  scsiq->d2.
								  target_ix));
			if (cur_target_qng < asc_dvc->max_dvc_qng[tid_no]) {
				scsi_busy = AscReadLramByte(iop_base, (ushort)
							    ASCV_SCSIBUSY_B);
				scsi_busy &= ~target_id;
				AscWriteLramByte(iop_base,
						 (ushort)ASCV_SCSIBUSY_B,
						 scsi_busy);
				asc_dvc->queue_full_or_busy &= ~target_id;
			}
		}
		if (asc_dvc->cur_total_qng >= n_q_used) {
			asc_dvc->cur_total_qng -= n_q_used;
			if (asc_dvc->cur_dvc_qng[tid_no] != 0) {
				asc_dvc->cur_dvc_qng[tid_no]--;
			}
		} else {
			AscSetLibErrorCode(asc_dvc, ASCQ_ERR_CUR_QNG);
			scsiq->d3.done_stat = QD_WITH_ERROR;
			goto FATAL_ERR_QDONE;
		}
		if ((scsiq->d2.srb_tag == 0UL) ||
		    ((scsiq->q_status & QS_ABORTED) != 0)) {
			return (0x11);
		} else if (scsiq->q_status == QS_DONE) {
			/*
			 * This is also curious.
			 * false_overrun will _always_ be set to 'false'
			 */
			false_overrun = false;
			if (scsiq->extra_bytes != 0) {
				scsiq->remain_bytes += scsiq->extra_bytes;
			}
			if (scsiq->d3.done_stat == QD_WITH_ERROR) {
				if (scsiq->d3.host_stat ==
				    QHSTA_M_DATA_OVER_RUN) {
					if ((scsiq->
					     cntl & (QC_DATA_IN | QC_DATA_OUT))
					    == 0) {
						scsiq->d3.done_stat =
						    QD_NO_ERROR;
						scsiq->d3.host_stat =
						    QHSTA_NO_ERROR;
					} else if (false_overrun) {
						scsiq->d3.done_stat =
						    QD_NO_ERROR;
						scsiq->d3.host_stat =
						    QHSTA_NO_ERROR;
					}
				} else if (scsiq->d3.host_stat ==
					   QHSTA_M_HUNG_REQ_SCSI_BUS_RESET) {
					AscStopChip(iop_base);
					AscSetChipControl(iop_base,
							  (uchar)(CC_SCSI_RESET
								  | CC_HALT));
					udelay(60);
					AscSetChipControl(iop_base, CC_HALT);
					AscSetChipStatus(iop_base,
							 CIW_CLR_SCSI_RESET_INT);
					AscSetChipStatus(iop_base, 0);
					AscSetChipControl(iop_base, 0);
				}
			}
			if ((scsiq->cntl & QC_NO_CALLBACK) == 0) {
				asc_isr_callback(asc_dvc, scsiq);
			} else {
				if ((AscReadLramByte(iop_base,
						     (ushort)(q_addr + (ushort)
							      ASC_SCSIQ_CDB_BEG))
				     == START_STOP)) {
					asc_dvc->unit_not_ready &= ~target_id;
					if (scsiq->d3.done_stat != QD_NO_ERROR) {
						asc_dvc->start_motor &=
						    ~target_id;
					}
				}
			}
			return (1);
		} else {
			AscSetLibErrorCode(asc_dvc, ASCQ_ERR_Q_STATUS);
 FATAL_ERR_QDONE:
			if ((scsiq->cntl & QC_NO_CALLBACK) == 0) {
				asc_isr_callback(asc_dvc, scsiq);
			}
			return (0x80);
		}
	}
	return (0);
}