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
struct osst_tape {int first_frame_position; size_t partition; int block_size; int /*<<< orphan*/  write_count; TYPE_2__* buffer; int /*<<< orphan*/  timeout; scalar_t__ logical_blk_num; int /*<<< orphan*/  frame_seq_number; int /*<<< orphan*/  write_type; TYPE_1__* ps; scalar_t__ poll; int /*<<< orphan*/  raw; } ;
struct osst_request {int* sense; } ;
struct TYPE_4__ {int buffer_bytes; scalar_t__ syscall_result; } ;
struct TYPE_3__ {int /*<<< orphan*/  rw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int EIO ; 
 int ENOSPC ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  OS_FRAME_SIZE ; 
 int /*<<< orphan*/  OS_FRAME_TYPE_DATA ; 
 int /*<<< orphan*/  OS_WRITE_DATA ; 
 int /*<<< orphan*/  ST_WRITING ; 
 int VOLUME_OVERFLOW ; 
 unsigned char WRITE_6 ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct osst_request* osst_do_scsi (struct osst_request*,struct osst_tape*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osst_flush_drive_buffer (struct osst_tape*,struct osst_request**) ; 
 int osst_get_frame_position (struct osst_tape*,struct osst_request**) ; 
 int /*<<< orphan*/  osst_init_aux (struct osst_tape*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  osst_position_tape_and_confirm (struct osst_tape*,struct osst_request**,int) ; 
 scalar_t__ osst_recover_wait_frame (struct osst_tape*,struct osst_request**,int) ; 
 scalar_t__ osst_wait_frame (struct osst_tape*,struct osst_request**,int,int,int) ; 
 scalar_t__ osst_write_error_recovery (struct osst_tape*,struct osst_request**,int) ; 

__attribute__((used)) static int osst_write_frame(struct osst_tape * STp, struct osst_request ** aSRpnt, int synchronous)
{
	unsigned char		cmd[MAX_COMMAND_SIZE];
	struct osst_request   * SRpnt;
	int			blks;
#if DEBUG
	char		      * name = tape_name(STp);
#endif

	if ((!STp-> raw) && (STp->first_frame_position == 0xbae)) { /* _must_ preserve buffer! */
#if DEBUG
		printk(OSST_DEB_MSG "%s:D: Reaching config partition.\n", name);
#endif
		if (osst_flush_drive_buffer(STp, aSRpnt) < 0) {
			return (-EIO);
		}
		/* error recovery may have bumped us past the header partition */
		if (osst_get_frame_position(STp, aSRpnt) < 0xbb8) {
#if DEBUG
			printk(OSST_DEB_MSG "%s:D: Skipping over config partition.\n", name);
#endif
		osst_position_tape_and_confirm(STp, aSRpnt, 0xbb8);
		}
	}

	if (STp->poll)
		if (osst_wait_frame (STp, aSRpnt, STp->first_frame_position, -48, 120))
			if (osst_recover_wait_frame(STp, aSRpnt, 1))
				return (-EIO);

//	osst_build_stats(STp, &SRpnt);

	STp->ps[STp->partition].rw = ST_WRITING;
	STp->write_type            = OS_WRITE_DATA;
			
	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0]   = WRITE_6;
	cmd[1]   = 1;
	cmd[4]   = 1;						/* one frame at a time... */
	blks     = STp->buffer->buffer_bytes / STp->block_size;
#if DEBUG
	if (debugging)
		printk(OSST_DEB_MSG "%s:D: Writing %d blocks to frame %d, lblks %d-%d\n", name, blks, 
			STp->frame_seq_number, STp->logical_blk_num - blks, STp->logical_blk_num - 1);
#endif
	osst_init_aux(STp, OS_FRAME_TYPE_DATA, STp->frame_seq_number++,
		      STp->logical_blk_num - blks, STp->block_size, blks);

#if DEBUG
	if (!synchronous)
		STp->write_pending = 1;
#endif
	SRpnt = osst_do_scsi(*aSRpnt, STp, cmd, OS_FRAME_SIZE, DMA_TO_DEVICE, STp->timeout,
									MAX_RETRIES, synchronous);
	if (!SRpnt)
		return (-EBUSY);
	*aSRpnt = SRpnt;

	if (synchronous) {
		if (STp->buffer->syscall_result != 0) {
#if DEBUG
			if (debugging)
				printk(OSST_DEB_MSG "%s:D: Error on write:\n", name);
#endif
			if ((SRpnt->sense[0] & 0x70) == 0x70 &&
			    (SRpnt->sense[2] & 0x40)) {
				if ((SRpnt->sense[2] & 0x0f) == VOLUME_OVERFLOW)
					return (-ENOSPC);
			}
			else {
				if (osst_write_error_recovery(STp, aSRpnt, 1))
					return (-EIO);
			}
		}
		else
			STp->first_frame_position++;
	}

	STp->write_count++;

	return 0;
}