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
struct osst_tape {int dirty; scalar_t__ frame_seq_number; scalar_t__ eod_frame_lfa; int /*<<< orphan*/  first_frame_position; int /*<<< orphan*/  eod_frame_ppos; int /*<<< orphan*/  write_type; scalar_t__ raw; } ;
struct osst_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OS_WRITE_EOD ; 
 int osst_flush_drive_buffer (struct osst_tape*,struct osst_request**) ; 
 int osst_flush_write_buffer (struct osst_tape*,struct osst_request**) ; 

__attribute__((used)) static int osst_write_eod(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	int	result;
#if DEBUG
	char  * name = tape_name(STp);
#endif

	if (STp->raw) return 0;

	STp->write_type = OS_WRITE_EOD;
	STp->eod_frame_ppos = STp->first_frame_position;
#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Writing EOD at fppos %d (fseq %d, lblk %d)\n", name,
			STp->eod_frame_ppos, STp->frame_seq_number, STp->logical_blk_num);
#endif
	STp->dirty = 1;

	result  = osst_flush_write_buffer(STp, aSRpnt);	
	result |= osst_flush_drive_buffer(STp, aSRpnt);
	STp->eod_frame_lfa = --(STp->frame_seq_number);
	return result;
}