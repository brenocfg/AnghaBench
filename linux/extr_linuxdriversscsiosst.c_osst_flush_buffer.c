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
struct st_partstat {scalar_t__ rw; scalar_t__ eof; scalar_t__ drv_file; scalar_t__ drv_block; } ;
struct osst_tape {scalar_t__ ready; size_t partition; int block_size; scalar_t__ logical_blk_num; scalar_t__ frame_in_buffer; TYPE_1__* buffer; int /*<<< orphan*/  can_bsr; int /*<<< orphan*/  write_type; scalar_t__ dirty; struct st_partstat* ps; scalar_t__ pos_unknown; } ;
struct osst_request {int dummy; } ;
struct TYPE_2__ {int buffer_bytes; int read_pointer; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OS_WRITE_DATA ; 
 scalar_t__ ST_FM_HIT ; 
 void* ST_NOEOF ; 
 scalar_t__ ST_READY ; 
 scalar_t__ ST_WRITING ; 
 int cross_eof (struct osst_tape*,struct osst_request**,int /*<<< orphan*/ ) ; 
 int osst_flush_write_buffer (struct osst_tape*,struct osst_request**) ; 
 int osst_seek_logical_blk (struct osst_tape*,struct osst_request**,scalar_t__) ; 

__attribute__((used)) static int osst_flush_buffer(struct osst_tape * STp, struct osst_request ** aSRpnt, int seek_next)
{
	struct st_partstat * STps;
	int    backspace = 0, result = 0;
#if DEBUG
	char * name = tape_name(STp);
#endif

	/*
	 * If there was a bus reset, block further access
	 * to this device.
	 */
	if( STp->pos_unknown)
		return (-EIO);

	if (STp->ready != ST_READY)
		return 0;

	STps = &(STp->ps[STp->partition]);
	if (STps->rw == ST_WRITING || STp->dirty) {	/* Writing */
		STp->write_type = OS_WRITE_DATA;
		return osst_flush_write_buffer(STp, aSRpnt);
	}
	if (STp->block_size == 0)
		return 0;

#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Reached flush (read) buffer\n", name);
#endif

	if (!STp->can_bsr) {
		backspace = ((STp->buffer)->buffer_bytes + (STp->buffer)->read_pointer) / STp->block_size -
			    ((STp->buffer)->read_pointer + STp->block_size - 1        ) / STp->block_size ;
		(STp->buffer)->buffer_bytes = 0;
		(STp->buffer)->read_pointer = 0;
		STp->frame_in_buffer = 0;		/* FIXME is this relevant w. OSST? */
	}

	if (!seek_next) {
		if (STps->eof == ST_FM_HIT) {
			result = cross_eof(STp, aSRpnt, 0); /* Back over the EOF hit */
			if (!result)
				STps->eof = ST_NOEOF;
			else {
				if (STps->drv_file >= 0)
					STps->drv_file++;
				STps->drv_block = 0;
			}
		}
		if (!result && backspace > 0)	/* TODO -- design and run a test case for this */
			result = osst_seek_logical_blk(STp, aSRpnt, STp->logical_blk_num - backspace);
	}
	else if (STps->eof == ST_FM_HIT) {
		if (STps->drv_file >= 0)
			STps->drv_file++;
		STps->drv_block = 0;
		STps->eof = ST_NOEOF;
	}

	return result;
}