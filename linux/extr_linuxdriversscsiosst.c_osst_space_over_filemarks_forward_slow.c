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
struct osst_tape {scalar_t__ first_frame_position; scalar_t__ eod_frame_ppos; TYPE_4__* buffer; int /*<<< orphan*/  logical_blk_num; scalar_t__ frame_in_buffer; int /*<<< orphan*/  frame_seq_number; } ;
struct osst_request {int dummy; } ;
struct TYPE_8__ {TYPE_3__* aux; scalar_t__ read_pointer; scalar_t__ buffer_bytes; } ;
struct TYPE_6__ {TYPE_1__* dat_list; } ;
struct TYPE_7__ {scalar_t__ frame_type; TYPE_2__ dat; } ;
struct TYPE_5__ {int /*<<< orphan*/  blk_cnt; } ;

/* Variables and functions */
 int EIO ; 
 int MTFSF ; 
 scalar_t__ OS_FRAME_TYPE_EOD ; 
 scalar_t__ OS_FRAME_TYPE_MARKER ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ osst_get_logical_frame (struct osst_tape*,struct osst_request**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osst_space_over_filemarks_forward_slow(struct osst_tape * STp, struct osst_request ** aSRpnt,
								     int mt_op, int mt_count)
{
	int	cnt = 0;
#if DEBUG
	char  * name = tape_name(STp);

	printk(OSST_DEB_MSG "%s:D: Reached space_over_filemarks_forward_slow %d %d\n", name, mt_op, mt_count);
#endif
	if (osst_get_logical_frame(STp, aSRpnt, -1, 0) < 0) {
#if DEBUG
		printk(OSST_DEB_MSG "%s:D: Couldn't get logical blk num in space_filemarks_fwd\n", name);
#endif
		return (-EIO);
	}
	while (1) {
		if (osst_get_logical_frame(STp, aSRpnt, -1, 0) < 0) {
#if DEBUG
			printk(OSST_DEB_MSG "%s:D: Couldn't get logical blk num in space_filemarks\n", name);
#endif
			return (-EIO);
		}
		if (STp->buffer->aux->frame_type == OS_FRAME_TYPE_MARKER)
			cnt++;
		if (STp->buffer->aux->frame_type == OS_FRAME_TYPE_EOD) {
#if DEBUG
			printk(OSST_DEB_MSG "%s:D: space_fwd: EOD reached\n", name);
#endif
			if (STp->first_frame_position > STp->eod_frame_ppos+1) {
#if DEBUG
				printk(OSST_DEB_MSG "%s:D: EOD position corrected (%d=>%d)\n",
					       	name, STp->eod_frame_ppos, STp->first_frame_position-1);
#endif
				STp->eod_frame_ppos = STp->first_frame_position-1;
			}
			return (-EIO);
		}
		if (cnt == mt_count)
			break;
		STp->frame_in_buffer = 0;
	}
	if (mt_op == MTFSF) {
		STp->frame_seq_number++;
		STp->frame_in_buffer      = 0;
		STp->buffer->buffer_bytes = 0;
		STp->buffer->read_pointer = 0;
		STp->logical_blk_num     += ntohs(STp->buffer->aux->dat.dat_list[0].blk_cnt);
	}
	return 0;
}