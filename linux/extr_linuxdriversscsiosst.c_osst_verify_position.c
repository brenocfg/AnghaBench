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
struct osst_tape {int first_frame_position; int frame_seq_number; int logical_blk_num; int frame_in_buffer; int linux_media_version; int filemark_cnt; size_t partition; int dirty; TYPE_5__* ps; TYPE_4__* buffer; TYPE_2__* header_cache; } ;
struct osst_request {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  rw; } ;
struct TYPE_9__ {int read_pointer; int buffer_bytes; TYPE_3__* aux; } ;
struct TYPE_8__ {scalar_t__ frame_type; int /*<<< orphan*/  last_mark_ppos; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fm_tab_ent; } ;
struct TYPE_7__ {TYPE_1__ dat_fm_tab; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ OS_FRAME_TYPE_MARKER ; 
 int /*<<< orphan*/  ST_WRITING ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ osst_get_logical_frame (struct osst_tape*,struct osst_request**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osst_set_frame_position (struct osst_tape*,struct osst_request**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osst_verify_position(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	int	frame_position  = STp->first_frame_position;
	int	frame_seq_numbr = STp->frame_seq_number;
	int	logical_blk_num = STp->logical_blk_num;
       	int	halfway_frame   = STp->frame_in_buffer;
	int	read_pointer    = STp->buffer->read_pointer;
	int	prev_mark_ppos  = -1;
	int	actual_mark_ppos, i, n;
#if DEBUG
	char  * name = tape_name(STp);

	printk(OSST_DEB_MSG "%s:D: Verify that the tape is really the one we think before writing\n", name);
#endif
	osst_set_frame_position(STp, aSRpnt, frame_position - 1, 0);
	if (osst_get_logical_frame(STp, aSRpnt, -1, 0) < 0) {
#if DEBUG
		printk(OSST_DEB_MSG "%s:D: Couldn't get logical blk num in verify_position\n", name);
#endif
		return (-EIO);
	}
	if (STp->linux_media_version >= 4) {
		for (i=0; i<STp->filemark_cnt; i++)
			if ((n=ntohl(STp->header_cache->dat_fm_tab.fm_tab_ent[i])) < frame_position)
				prev_mark_ppos = n;
	} else
		prev_mark_ppos = frame_position - 1;  /* usually - we don't really know */
	actual_mark_ppos = STp->buffer->aux->frame_type == OS_FRAME_TYPE_MARKER ?
				frame_position - 1 : ntohl(STp->buffer->aux->last_mark_ppos);
	if (frame_position  != STp->first_frame_position                   ||
	    frame_seq_numbr != STp->frame_seq_number + (halfway_frame?0:1) ||
	    prev_mark_ppos  != actual_mark_ppos                            ) {
#if DEBUG
		printk(OSST_DEB_MSG "%s:D: Block mismatch: fppos %d-%d, fseq %d-%d, mark %d-%d\n", name,
				  STp->first_frame_position, frame_position, 
				  STp->frame_seq_number + (halfway_frame?0:1),
				  frame_seq_numbr, actual_mark_ppos, prev_mark_ppos);
#endif
		return (-EIO);
	}
	if (halfway_frame) {
		/* prepare buffer for append and rewrite on top of original */
		osst_set_frame_position(STp, aSRpnt, frame_position - 1, 0);
		STp->buffer->buffer_bytes  = read_pointer;
		STp->ps[STp->partition].rw = ST_WRITING;
		STp->dirty                 = 1;
	}
	STp->frame_in_buffer  = halfway_frame;
	STp->frame_seq_number = frame_seq_numbr;
	STp->logical_blk_num  = logical_blk_num;
	return 0;
}