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
struct TYPE_2__ {size_t frame_max; int /*<<< orphan*/  count_max; int /*<<< orphan*/  head; } ;
union ep_buffer_info {TYPE_1__ v1i; } ;
struct esmem_frame {void* frame_data; scalar_t__ frame_size; } ;
struct epbuf_handler {int /*<<< orphan*/ * ring; union ep_buffer_info* info; } ;

/* Variables and functions */
 size_t EP_RING_INDEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *fjes_hw_epbuf_rx_curpkt_get_addr(struct epbuf_handler *epbh,
				       size_t *psize)
{
	union ep_buffer_info *info = epbh->info;
	struct esmem_frame *ring_frame;
	void *frame;

	ring_frame = (struct esmem_frame *)&(epbh->ring[EP_RING_INDEX
					     (info->v1i.head,
					      info->v1i.count_max) *
					     info->v1i.frame_max]);

	*psize = (size_t)ring_frame->frame_size;

	frame = ring_frame->frame_data;

	return frame;
}