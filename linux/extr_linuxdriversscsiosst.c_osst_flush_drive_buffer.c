#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct osst_tape {size_t partition; TYPE_2__* ps; TYPE_1__* buffer; int /*<<< orphan*/  timeout; } ;
struct osst_request {int* sense; } ;
struct TYPE_4__ {int /*<<< orphan*/  rw; } ;
struct TYPE_3__ {scalar_t__ syscall_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int EBUSY ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int OSST_WAIT_LONG_WRITE_COMPLETE ; 
 int OSST_WAIT_WRITE_COMPLETE ; 
 int /*<<< orphan*/  OS_WRITING_COMPLETE ; 
 unsigned char WRITE_FILEMARKS ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct osst_request* osst_do_scsi (struct osst_request*,struct osst_tape*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int osst_wait_ready (struct osst_tape*,struct osst_request**,int,int) ; 
 int osst_write_error_recovery (struct osst_tape*,struct osst_request**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osst_flush_drive_buffer(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	unsigned char		cmd[MAX_COMMAND_SIZE];
	struct osst_request   * SRpnt;
	int			result = 0;
	int			delay  = OSST_WAIT_WRITE_COMPLETE;
#if DEBUG
	char		      * name = tape_name(STp);

	printk(OSST_DEB_MSG "%s:D: Reached onstream flush drive buffer (write filemark)\n", name);
#endif

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = WRITE_FILEMARKS;
	cmd[1] = 1;

	SRpnt = osst_do_scsi(*aSRpnt, STp, cmd, 0, DMA_NONE, STp->timeout, MAX_RETRIES, 1);
	*aSRpnt = SRpnt;
	if (!SRpnt) return (-EBUSY);
	if (STp->buffer->syscall_result) {
		if ((SRpnt->sense[2] & 0x0f) == 2 && SRpnt->sense[12] == 4) {
			if (SRpnt->sense[13] == 8) {
				delay = OSST_WAIT_LONG_WRITE_COMPLETE;
			}
		} else
			result = osst_write_error_recovery(STp, aSRpnt, 0);
	}
	result |= osst_wait_ready(STp, aSRpnt, 5 * 60, delay);
	STp->ps[STp->partition].rw = OS_WRITING_COMPLETE;

	return (result);
}