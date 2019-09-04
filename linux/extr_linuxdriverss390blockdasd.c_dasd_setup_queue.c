#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_dev_sectors; unsigned int discard_granularity; void* discard_alignment; } ;
struct request_queue {TYPE_3__ limits; } ;
struct dasd_block {unsigned int bp_block; int s2b_shift; TYPE_2__* base; struct request_queue* request_queue; } ;
struct TYPE_5__ {int features; TYPE_1__* discipline; } ;
struct TYPE_4__ {int max_blocks; } ;

/* Variables and functions */
 void* ALIGN (unsigned int,void*) ; 
 int DASD_FEATURE_DISCARD ; 
 int DASD_FEATURE_USERAW ; 
 void* PAGE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 unsigned int USHRT_MAX ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (struct request_queue*,void*) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_max_write_zeroes_sectors (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (struct request_queue*,void*) ; 

__attribute__((used)) static void dasd_setup_queue(struct dasd_block *block)
{
	unsigned int logical_block_size = block->bp_block;
	struct request_queue *q = block->request_queue;
	unsigned int max_bytes, max_discard_sectors;
	int max;

	if (block->base->features & DASD_FEATURE_USERAW) {
		/*
		 * the max_blocks value for raw_track access is 256
		 * it is higher than the native ECKD value because we
		 * only need one ccw per track
		 * so the max_hw_sectors are
		 * 2048 x 512B = 1024kB = 16 tracks
		 */
		max = 2048;
	} else {
		max = block->base->discipline->max_blocks << block->s2b_shift;
	}
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	q->limits.max_dev_sectors = max;
	blk_queue_logical_block_size(q, logical_block_size);
	blk_queue_max_hw_sectors(q, max);
	blk_queue_max_segments(q, USHRT_MAX);
	/* with page sized segments we can translate each segement into
	 * one idaw/tidaw
	 */
	blk_queue_max_segment_size(q, PAGE_SIZE);
	blk_queue_segment_boundary(q, PAGE_SIZE - 1);

	/* Only activate blocklayer discard support for devices that support it */
	if (block->base->features & DASD_FEATURE_DISCARD) {
		q->limits.discard_granularity = logical_block_size;
		q->limits.discard_alignment = PAGE_SIZE;

		/* Calculate max_discard_sectors and make it PAGE aligned */
		max_bytes = USHRT_MAX * logical_block_size;
		max_bytes = ALIGN(max_bytes, PAGE_SIZE) - PAGE_SIZE;
		max_discard_sectors = max_bytes / logical_block_size;

		blk_queue_max_discard_sectors(q, max_discard_sectors);
		blk_queue_max_write_zeroes_sectors(q, max_discard_sectors);
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
	}
}