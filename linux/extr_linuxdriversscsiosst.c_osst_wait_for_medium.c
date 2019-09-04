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
struct osst_tape {TYPE_1__* buffer; int /*<<< orphan*/  timeout; } ;
struct osst_request {int* sense; } ;
struct TYPE_2__ {scalar_t__ syscall_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int EBUSY ; 
 unsigned int HZ ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 unsigned char TEST_UNIT_READY ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct osst_request* osst_do_scsi (struct osst_request*,struct osst_tape*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int osst_wait_for_medium(struct osst_tape * STp, struct osst_request ** aSRpnt, unsigned timeout)
{
	unsigned char		cmd[MAX_COMMAND_SIZE];
	struct osst_request   * SRpnt;
	unsigned long		startwait = jiffies;
#if DEBUG
	int			dbg = debugging;
	char    	      * name = tape_name(STp);

	printk(OSST_DEB_MSG "%s:D: Reached onstream wait for medium\n", name);
#endif

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = TEST_UNIT_READY;

	SRpnt = osst_do_scsi(*aSRpnt, STp, cmd, 0, DMA_NONE, STp->timeout, MAX_RETRIES, 1);
	*aSRpnt = SRpnt;
	if (!SRpnt) return (-EBUSY);

	while ( STp->buffer->syscall_result && time_before(jiffies, startwait + timeout*HZ) &&
		SRpnt->sense[2] == 2 && SRpnt->sense[12] == 0x3a && SRpnt->sense[13] == 0  ) {
#if DEBUG
	    if (debugging) {
		printk(OSST_DEB_MSG "%s:D: Sleeping in onstream wait medium\n", name);
		printk(OSST_DEB_MSG "%s:D: Turning off debugging for a while\n", name);
		debugging = 0;
	    }
#endif
	    msleep(100);

	    memset(cmd, 0, MAX_COMMAND_SIZE);
	    cmd[0] = TEST_UNIT_READY;

	    SRpnt = osst_do_scsi(SRpnt, STp, cmd, 0, DMA_NONE, STp->timeout, MAX_RETRIES, 1);
	}
	*aSRpnt = SRpnt;
#if DEBUG
	debugging = dbg;
#endif
	if ( STp->buffer->syscall_result     && SRpnt->sense[2]  != 2 &&
	     SRpnt->sense[12] != 4 && SRpnt->sense[13] == 1) {
#if DEBUG
	    printk(OSST_DEB_MSG "%s:D: Abnormal exit from onstream wait medium\n", name);
	    printk(OSST_DEB_MSG "%s:D: Result = %d, Sense: 0=%02x, 2=%02x, 12=%02x, 13=%02x\n", name,
			STp->buffer->syscall_result, SRpnt->sense[0], SRpnt->sense[2],
			SRpnt->sense[12], SRpnt->sense[13]);
#endif
	    return 0;
	}
#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Normal exit from onstream wait medium\n", name);
#endif
	return 1;
}