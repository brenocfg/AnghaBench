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
struct TYPE_2__ {int tp_block_size; int tp_frame_size; unsigned int tp_block_nr; int tp_frame_nr; } ;
struct ring {int mm_len; int rd_num; int flen; TYPE_1__ req; int /*<<< orphan*/  walk; } ;

/* Variables and functions */
 int TPACKET_ALIGNMENT ; 
 int getpagesize () ; 
 int /*<<< orphan*/  walk_v1_v2 ; 

__attribute__((used)) static void __v1_v2_fill(struct ring *ring, unsigned int blocks)
{
	ring->req.tp_block_size = getpagesize() << 2;
	ring->req.tp_frame_size = TPACKET_ALIGNMENT << 7;
	ring->req.tp_block_nr = blocks;

	ring->req.tp_frame_nr = ring->req.tp_block_size /
				ring->req.tp_frame_size *
				ring->req.tp_block_nr;

	ring->mm_len = ring->req.tp_block_size * ring->req.tp_block_nr;
	ring->walk = walk_v1_v2;
	ring->rd_num = ring->req.tp_frame_nr;
	ring->flen = ring->req.tp_frame_size;
}