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
struct TYPE_2__ {int tp_retire_blk_tov; int tp_block_size; int tp_frame_size; unsigned int tp_block_nr; int tp_frame_nr; int /*<<< orphan*/  tp_feature_req_word; scalar_t__ tp_sizeof_priv; } ;
struct ring {int mm_len; int rd_num; int flen; TYPE_1__ req3; int /*<<< orphan*/  walk; } ;

/* Variables and functions */
 int PACKET_RX_RING ; 
 int TPACKET_ALIGNMENT ; 
 int /*<<< orphan*/  TP_FT_REQ_FILL_RXHASH ; 
 int getpagesize () ; 
 int /*<<< orphan*/  walk_v3 ; 

__attribute__((used)) static void __v3_fill(struct ring *ring, unsigned int blocks, int type)
{
	if (type == PACKET_RX_RING) {
		ring->req3.tp_retire_blk_tov = 64;
		ring->req3.tp_sizeof_priv = 0;
		ring->req3.tp_feature_req_word = TP_FT_REQ_FILL_RXHASH;
	}
	ring->req3.tp_block_size = getpagesize() << 2;
	ring->req3.tp_frame_size = TPACKET_ALIGNMENT << 7;
	ring->req3.tp_block_nr = blocks;

	ring->req3.tp_frame_nr = ring->req3.tp_block_size /
				 ring->req3.tp_frame_size *
				 ring->req3.tp_block_nr;

	ring->mm_len = ring->req3.tp_block_size * ring->req3.tp_block_nr;
	ring->walk = walk_v3;
	ring->rd_num = ring->req3.tp_block_nr;
	ring->flen = ring->req3.tp_block_size;
}