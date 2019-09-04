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
struct mite_ring {unsigned int n_links; int dma_addr; struct mite_dma_desc* descs; } ;
struct mite_dma_desc {void* next; void* addr; void* count; } ;
struct comedi_subdevice {TYPE_1__* device; struct comedi_async* async; } ;
struct comedi_async {TYPE_3__* buf_map; } ;
struct TYPE_6__ {TYPE_2__* page_list; } ;
struct TYPE_5__ {unsigned int dma_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

int mite_init_ring_descriptors(struct mite_ring *ring,
			       struct comedi_subdevice *s,
			       unsigned int nbytes)
{
	struct comedi_async *async = s->async;
	struct mite_dma_desc *desc = NULL;
	unsigned int n_full_links = nbytes >> PAGE_SHIFT;
	unsigned int remainder = nbytes % PAGE_SIZE;
	int i;

	dev_dbg(s->device->class_dev,
		"mite: init ring buffer to %u bytes\n", nbytes);

	if ((n_full_links + (remainder > 0 ? 1 : 0)) > ring->n_links) {
		dev_err(s->device->class_dev,
			"mite: ring buffer too small for requested init\n");
		return -ENOMEM;
	}

	/* We set the descriptors for all full links. */
	for (i = 0; i < n_full_links; ++i) {
		desc = &ring->descs[i];
		desc->count = cpu_to_le32(PAGE_SIZE);
		desc->addr = cpu_to_le32(async->buf_map->page_list[i].dma_addr);
		desc->next = cpu_to_le32(ring->dma_addr +
					 (i + 1) * sizeof(*desc));
	}

	/* the last link is either a remainder or was a full link. */
	if (remainder > 0) {
		desc = &ring->descs[i];
		/* set the lesser count for the remainder link */
		desc->count = cpu_to_le32(remainder);
		desc->addr = cpu_to_le32(async->buf_map->page_list[i].dma_addr);
	}

	/* Assign the last link->next to point back to the head of the list. */
	desc->next = cpu_to_le32(ring->dma_addr);

	/*
	 * barrier is meant to insure that all the writes to the dma descriptors
	 * have completed before the dma controller is commanded to read them
	 */
	smp_wmb();
	return 0;
}