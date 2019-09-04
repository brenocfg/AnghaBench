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
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_3__ {size_t desc_count; scalar_t__ base_addr; } ;
struct vnic_rq {scalar_t__ buf_index; TYPE_2__* ctrl; int /*<<< orphan*/ ** bufs; int /*<<< orphan*/ * to_clean; int /*<<< orphan*/ * to_use; TYPE_1__ ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  posted_index; int /*<<< orphan*/  fetch_index; int /*<<< orphan*/  error_status; int /*<<< orphan*/  dropped_packet_count; int /*<<< orphan*/  error_interrupt_offset; int /*<<< orphan*/  error_interrupt_enable; int /*<<< orphan*/  cq_index; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  ring_base; } ;

/* Variables and functions */
 int VNIC_PADDR_TARGET ; 
 size_t VNIC_RQ_BUF_BLK_ENTRIES ; 
 size_t ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

void vnic_rq_init(struct vnic_rq *rq, unsigned int cq_index,
	unsigned int error_interrupt_enable,
	unsigned int error_interrupt_offset)
{
	u64 paddr;
	u32 fetch_index;

	paddr = (u64)rq->ring.base_addr | VNIC_PADDR_TARGET;
	writeq(paddr, &rq->ctrl->ring_base);
	iowrite32(rq->ring.desc_count, &rq->ctrl->ring_size);
	iowrite32(cq_index, &rq->ctrl->cq_index);
	iowrite32(error_interrupt_enable, &rq->ctrl->error_interrupt_enable);
	iowrite32(error_interrupt_offset, &rq->ctrl->error_interrupt_offset);
	iowrite32(0, &rq->ctrl->dropped_packet_count);
	iowrite32(0, &rq->ctrl->error_status);

	/* Use current fetch_index as the ring starting point */
	fetch_index = ioread32(&rq->ctrl->fetch_index);
	rq->to_use = rq->to_clean =
		&rq->bufs[fetch_index / VNIC_RQ_BUF_BLK_ENTRIES]
			[fetch_index % VNIC_RQ_BUF_BLK_ENTRIES];
	iowrite32(fetch_index, &rq->ctrl->posted_index);

	rq->buf_index = 0;
}