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
struct vring_desc {unsigned long addr; unsigned int len; unsigned int next; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {void* data; } ;
struct TYPE_7__ {unsigned int free_head; scalar_t__ avail_idx; int /*<<< orphan*/  num_free; } ;
struct TYPE_6__ {TYPE_1__* avail; struct vring_desc* desc; } ;
struct TYPE_5__ {unsigned int* ring; scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRING_DESC_F_NEXT ; 
 TYPE_4__* data ; 
 TYPE_3__ guest ; 
 TYPE_2__ ring ; 
 int ring_size ; 
 int /*<<< orphan*/  smp_release () ; 

int add_inbuf(unsigned len, void *buf, void *datap)
{
	unsigned head;
#ifndef INORDER
	unsigned avail;
#endif
	struct vring_desc *desc;

	if (!guest.num_free)
		return -1;

#ifdef INORDER
	head = (ring_size - 1) & (guest.avail_idx++);
#else
	head = guest.free_head;
#endif
	guest.num_free--;

	desc = ring.desc;
	desc[head].flags = VRING_DESC_F_NEXT;
	desc[head].addr = (unsigned long)(void *)buf;
	desc[head].len = len;
	/* We do it like this to simulate the way
	 * we'd have to flip it if we had multiple
	 * descriptors.
	 */
	desc[head].flags &= ~VRING_DESC_F_NEXT;
#ifndef INORDER
	guest.free_head = desc[head].next;
#endif

	data[head].data = datap;

#ifdef RING_POLL
	/* Barrier A (for pairing) */
	smp_release();
	avail = guest.avail_idx++;
	ring.avail->ring[avail & (ring_size - 1)] =
		(head | (avail & ~(ring_size - 1))) ^ 0x8000;
#else
#ifndef INORDER
	/* Barrier A (for pairing) */
	smp_release();
	avail = (ring_size - 1) & (guest.avail_idx++);
	ring.avail->ring[avail] = head;
#endif
	/* Barrier A (for pairing) */
	smp_release();
#endif
	ring.avail->idx = guest.avail_idx;
	return 0;
}