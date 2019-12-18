#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int last_used_idx; unsigned int free_head; int /*<<< orphan*/  num_free; } ;
struct TYPE_10__ {TYPE_3__* desc; TYPE_2__* used; } ;
struct TYPE_9__ {unsigned int len; unsigned int next; scalar_t__ addr; } ;
struct TYPE_8__ {unsigned int idx; TYPE_1__* ring; } ;
struct TYPE_7__ {unsigned int id; unsigned int len; } ;

/* Variables and functions */
 TYPE_6__* data ; 
 TYPE_5__ guest ; 
 TYPE_4__ ring ; 
 int ring_size ; 
 int /*<<< orphan*/  smp_acquire () ; 

void *get_buf(unsigned *lenp, void **bufp)
{
	unsigned head;
	unsigned index;
	void *datap;

#ifdef RING_POLL
	head = (ring_size - 1) & guest.last_used_idx;
	index = ring.used->ring[head].id;
	if ((index ^ guest.last_used_idx ^ 0x8000) & ~(ring_size - 1))
		return NULL;
	/* Barrier B (for pairing) */
	smp_acquire();
	index &= ring_size - 1;
#else
	if (ring.used->idx == guest.last_used_idx)
		return NULL;
	/* Barrier B (for pairing) */
	smp_acquire();
#ifdef INORDER
	head = (ring_size - 1) & guest.last_used_idx;
	index = head;
#else
	head = (ring_size - 1) & guest.last_used_idx;
	index = ring.used->ring[head].id;
#endif

#endif
#ifdef INORDER
	*lenp = ring.desc[index].len;
#else
	*lenp = ring.used->ring[head].len;
#endif
	datap = data[index].data;
	*bufp = (void*)(unsigned long)ring.desc[index].addr;
	data[index].data = NULL;
#ifndef INORDER
	ring.desc[index].next = guest.free_head;
	guest.free_head = index;
#endif
	guest.num_free++;
	guest.last_used_idx++;
	return datap;
}