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
struct TYPE_6__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {int last_used_idx; int /*<<< orphan*/  num_free; } ;
struct TYPE_4__ {int flags; unsigned int len; int index; } ;

/* Variables and functions */
 int DESC_HW ; 
 TYPE_3__* data ; 
 TYPE_2__ guest ; 
 TYPE_1__* ring ; 
 int ring_size ; 
 int /*<<< orphan*/  smp_acquire () ; 

void *get_buf(unsigned *lenp, void **bufp)
{
	unsigned head = (ring_size - 1) & guest.last_used_idx;
	unsigned index;
	void *datap;

	if (ring[head].flags & DESC_HW)
		return NULL;
	/* Barrier B (for pairing) */
	smp_acquire();
	*lenp = ring[head].len;
	index = ring[head].index & (ring_size - 1);
	datap = data[index].data;
	*bufp = data[index].buf;
	data[index].buf = NULL;
	data[index].data = NULL;
	guest.num_free++;
	guest.last_used_idx++;
	return datap;
}