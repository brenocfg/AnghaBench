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
struct TYPE_6__ {void* data; void* buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  avail_idx; int /*<<< orphan*/  num_free; } ;
struct TYPE_4__ {unsigned long addr; unsigned int len; unsigned int index; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_HW ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_3__* data ; 
 TYPE_2__ guest ; 
 TYPE_1__* ring ; 
 int ring_size ; 
 int /*<<< orphan*/  smp_release () ; 

int add_inbuf(unsigned len, void *buf, void *datap)
{
	unsigned head, index;

	if (!guest.num_free)
		return -1;

	guest.num_free--;
	head = (ring_size - 1) & (guest.avail_idx++);

	/* Start with a write. On MESI architectures this helps
	 * avoid a shared state with consumer that is polling this descriptor.
	 */
	ring[head].addr = (unsigned long)(void*)buf;
	ring[head].len = len;
	/* read below might bypass write above. That is OK because it's just an
	 * optimization. If this happens, we will get the cache line in a
	 * shared state which is unfortunate, but probably not worth it to
	 * add an explicit full barrier to avoid this.
	 */
	barrier();
	index = ring[head].index;
	data[index].buf = buf;
	data[index].data = datap;
	/* Barrier A (for pairing) */
	smp_release();
	ring[head].flags = DESC_HW;

	return 0;
}