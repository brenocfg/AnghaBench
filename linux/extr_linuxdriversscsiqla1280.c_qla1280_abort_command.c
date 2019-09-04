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
typedef  int uint16_t ;
struct srb {int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; } ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 unsigned int BIT_7 ; 
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  LEAVE (char*) ; 
 int MAILBOX_REGISTER_COUNT ; 
 int MBC_ABORT_COMMAND ; 
 unsigned int SCSI_BUS_32 (int /*<<< orphan*/ ) ; 
 unsigned int SCSI_LUN_32 (int /*<<< orphan*/ ) ; 
 unsigned int SCSI_TCN_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRB_ABORT_PENDING ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int qla1280_mailbox_command (struct scsi_qla_host*,int,int*) ; 

__attribute__((used)) static int
qla1280_abort_command(struct scsi_qla_host *ha, struct srb * sp, int handle)
{
	uint16_t mb[MAILBOX_REGISTER_COUNT];
	unsigned int bus, target, lun;
	int status;

	ENTER("qla1280_abort_command");

	bus = SCSI_BUS_32(sp->cmd);
	target = SCSI_TCN_32(sp->cmd);
	lun = SCSI_LUN_32(sp->cmd);

	sp->flags |= SRB_ABORT_PENDING;

	mb[0] = MBC_ABORT_COMMAND;
	mb[1] = (bus ? target | BIT_7 : target) << 8 | lun;
	mb[2] = handle >> 16;
	mb[3] = handle & 0xffff;
	status = qla1280_mailbox_command(ha, 0x0f, &mb[0]);

	if (status) {
		dprintk(2, "qla1280_abort_command: **** FAILED ****\n");
		sp->flags &= ~SRB_ABORT_PENDING;
	}


	LEAVE("qla1280_abort_command");
	return status;
}