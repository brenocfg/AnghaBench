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
struct st_partstat {int drv_file; int drv_block; scalar_t__ eof; } ;
struct osst_tape {size_t partition; int capacity; int first_data_ppos; int frame_seq_number; int logical_blk_num; int block_size; scalar_t__ first_frame_position; scalar_t__ eod_frame_ppos; TYPE_4__* buffer; scalar_t__ frame_in_buffer; struct st_partstat* ps; } ;
struct osst_request {int dummy; } ;
struct TYPE_8__ {int read_pointer; int buffer_bytes; TYPE_3__* aux; } ;
struct TYPE_6__ {TYPE_1__* dat_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  last_mark_lbn; int /*<<< orphan*/  filemark_cnt; TYPE_2__ dat; } ;
struct TYPE_5__ {int /*<<< orphan*/  blk_cnt; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int OSST_FRAME_SHIFT ; 
 int OSST_SECTOR_MASK ; 
 int OSST_SECTOR_SHIFT ; 
 scalar_t__ ST_EOD ; 
 scalar_t__ ST_FM_HIT ; 
 scalar_t__ ST_NOEOF ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int osst_get_frame_position (struct osst_tape*,struct osst_request**) ; 
 int osst_get_logical_frame (struct osst_tape*,struct osst_request**,int,int) ; 
 int osst_set_frame_position (struct osst_tape*,struct osst_request**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osst_seek_sector(struct osst_tape * STp, struct osst_request ** aSRpnt, int sector)
{
        struct st_partstat * STps   = &(STp->ps[STp->partition]);
	int		     frame  = sector >> OSST_FRAME_SHIFT,
			     offset = (sector & OSST_SECTOR_MASK) << OSST_SECTOR_SHIFT, 
			     r;
#if DEBUG
	char          * name = tape_name(STp);

	printk(OSST_DEB_MSG "%s:D: Seeking sector %d in frame %d at offset %d\n",
				name, sector, frame, offset);
#endif
	if (frame < 0 || frame >= STp->capacity) return (-ENXIO);

	if (frame <= STp->first_data_ppos) {
		STp->frame_seq_number = STp->logical_blk_num = STps->drv_file = STps->drv_block = 0;
		return (osst_set_frame_position(STp, aSRpnt, frame, 0));
	}
	r = osst_set_frame_position(STp, aSRpnt, offset?frame:frame-1, 0);
	if (r < 0) return r;

	r = osst_get_logical_frame(STp, aSRpnt, -1, 1);
	if (r < 0) return r;

	if (osst_get_frame_position(STp, aSRpnt) != (offset?frame+1:frame)) return (-EIO);

	if (offset) {
		STp->logical_blk_num      += offset / STp->block_size;
		STp->buffer->read_pointer  = offset;
		STp->buffer->buffer_bytes -= offset;
	} else {
		STp->frame_seq_number++;
		STp->frame_in_buffer       = 0;
		STp->logical_blk_num      += ntohs(STp->buffer->aux->dat.dat_list[0].blk_cnt);
		STp->buffer->buffer_bytes  = STp->buffer->read_pointer = 0;
	}
	STps->drv_file = ntohl(STp->buffer->aux->filemark_cnt);
	if (STps->eof == ST_FM_HIT) {
		STps->drv_file++;
		STps->drv_block = 0;
	} else {
		STps->drv_block = ntohl(STp->buffer->aux->last_mark_lbn)?
				    STp->logical_blk_num -
					(STps->drv_file ? ntohl(STp->buffer->aux->last_mark_lbn) + 1 : 0):
				  -1;
	}
	STps->eof       = (STp->first_frame_position >= STp->eod_frame_ppos)?ST_EOD:ST_NOEOF;
#if DEBUG
	printk(OSST_DEB_MSG 
		"%s:D: Now positioned at ppos %d, frame %d, lbn %d, file %d, blk %d, rptr %d, eof %d\n",
		name, STp->first_frame_position, STp->frame_seq_number, STp->logical_blk_num,
		STps->drv_file, STps->drv_block, STp->buffer->read_pointer, STps->eof);
#endif
	return 0;
}