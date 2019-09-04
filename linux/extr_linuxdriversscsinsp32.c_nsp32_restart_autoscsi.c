#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_10__ {unsigned int BaseAddress; int trans_method; TYPE_4__* cur_lunt; TYPE_3__* cur_target; } ;
typedef  TYPE_5__ nsp32_hw_data ;
struct TYPE_9__ {int /*<<< orphan*/  sglun_paddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sample_reg; int /*<<< orphan*/  ackwidth; int /*<<< orphan*/  syncreg; } ;
struct TYPE_7__ {TYPE_1__* host; } ;
struct TYPE_6__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_WIDTH ; 
 unsigned short ALL_COUNTER_CLR ; 
 unsigned short AUTOSCSI_RESTART ; 
 unsigned short AUTO_COMMAND_PHASE ; 
 unsigned short BM_START ; 
 unsigned short CB_IO_MODE ; 
 unsigned short CB_MMIO_MODE ; 
 unsigned short CLEAR_CDB_FIFO_POINTER ; 
 int /*<<< orphan*/  COMMAND_CONTROL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NSP32_DEBUG_RESTART ; 
 int NSP32_TRANSFER_BUSMASTER ; 
 int NSP32_TRANSFER_MMIO ; 
 int NSP32_TRANSFER_PIO ; 
 int /*<<< orphan*/  SGT_ADR ; 
 int /*<<< orphan*/  SREQ_SMPL_RATE ; 
 int /*<<< orphan*/  SYNC_REG ; 
 int /*<<< orphan*/  TRANSFER_CONTROL ; 
 unsigned short TRANSFER_GO ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_write1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  nsp32_write4 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static void nsp32_restart_autoscsi(struct scsi_cmnd *SCpnt, unsigned short command)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	unsigned int   base = data->BaseAddress;
	unsigned short transfer = 0;

	nsp32_dbg(NSP32_DEBUG_RESTART, "enter");

	if (data->cur_target == NULL || data->cur_lunt == NULL) {
		nsp32_msg(KERN_ERR, "Target or Lun is invalid");
	}

	/*
	 * set SYNC_REG
	 * Don't set BM_START_ADR before setting this register.
	 */
	nsp32_write1(base, SYNC_REG, data->cur_target->syncreg);

	/*
	 * set ACKWIDTH
	 */
	nsp32_write1(base, ACK_WIDTH, data->cur_target->ackwidth);

	/*
	 * set SREQ hazard killer sampling rate
	 */
	nsp32_write1(base, SREQ_SMPL_RATE, data->cur_target->sample_reg);

	/*
	 * set SGT ADDR (physical address)
	 */
	nsp32_write4(base, SGT_ADR, data->cur_lunt->sglun_paddr);

	/*
	 * set TRANSFER CONTROL REG
	 */
	transfer = 0;
	transfer |= (TRANSFER_GO | ALL_COUNTER_CLR);
	if (data->trans_method & NSP32_TRANSFER_BUSMASTER) {
		if (scsi_bufflen(SCpnt) > 0) {
			transfer |= BM_START;
		}
	} else if (data->trans_method & NSP32_TRANSFER_MMIO) {
		transfer |= CB_MMIO_MODE;
	} else if (data->trans_method & NSP32_TRANSFER_PIO) {
		transfer |= CB_IO_MODE;
	}
	nsp32_write2(base, TRANSFER_CONTROL, transfer);

	/*
	 * restart AutoSCSI
	 *
	 * TODO: COMMANDCONTROL_AUTO_COMMAND_PHASE is needed ?
	 */
	command |= (CLEAR_CDB_FIFO_POINTER |
		    AUTO_COMMAND_PHASE     |
		    AUTOSCSI_RESTART       );
	nsp32_write2(base, COMMAND_CONTROL, command);

	nsp32_dbg(NSP32_DEBUG_RESTART, "exit");
}