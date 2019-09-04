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
struct osst_tape {size_t partition; int first_frame_position; TYPE_1__* buffer; TYPE_2__* ps; scalar_t__ frame_in_buffer; } ;
struct osst_request {int dummy; } ;
struct TYPE_4__ {scalar_t__ drv_block; scalar_t__ rw; } ;
struct TYPE_3__ {int buffer_bytes; int read_pointer; } ;

/* Variables and functions */
 int OSST_FRAME_SHIFT ; 
 int OSST_SECTOR_MASK ; 
 int OSST_SECTOR_SHIFT ; 
 scalar_t__ ST_WRITING ; 
 int osst_get_frame_position (struct osst_tape*,struct osst_request**) ; 

__attribute__((used)) static int osst_get_sector(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	int	sector;
#if DEBUG
	char  * name = tape_name(STp);
	
	printk(OSST_DEB_MSG 
		"%s:D: Positioned at ppos %d, frame %d, lbn %d, file %d, blk %d, %cptr %d, eof %d\n",
		name, STp->first_frame_position, STp->frame_seq_number, STp->logical_blk_num,
		STp->ps[STp->partition].drv_file, STp->ps[STp->partition].drv_block, 
		STp->ps[STp->partition].rw == ST_WRITING?'w':'r',
		STp->ps[STp->partition].rw == ST_WRITING?STp->buffer->buffer_bytes:
		STp->buffer->read_pointer, STp->ps[STp->partition].eof);
#endif
	/* do we know where we are inside a file? */
	if (STp->ps[STp->partition].drv_block >= 0) {
		sector = (STp->frame_in_buffer ? STp->first_frame_position-1 :
				STp->first_frame_position) << OSST_FRAME_SHIFT;
		if (STp->ps[STp->partition].rw == ST_WRITING)
		       	sector |= (STp->buffer->buffer_bytes >> OSST_SECTOR_SHIFT) & OSST_SECTOR_MASK;
		else
	       		sector |= (STp->buffer->read_pointer >> OSST_SECTOR_SHIFT) & OSST_SECTOR_MASK;
	} else {
		sector = osst_get_frame_position(STp, aSRpnt);
		if (sector > 0)
			sector <<= OSST_FRAME_SHIFT;
	}
	return sector;
}