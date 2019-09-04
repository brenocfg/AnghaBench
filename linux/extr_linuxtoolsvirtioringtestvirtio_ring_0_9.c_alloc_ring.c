#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int kicked_avail_idx; int num_free; scalar_t__ free_head; scalar_t__ last_used_idx; scalar_t__ avail_idx; } ;
struct TYPE_8__ {int called_used_idx; scalar_t__ used_idx; } ;
struct TYPE_7__ {TYPE_1__* desc; } ;
struct TYPE_6__ {int next; } ;

/* Variables and functions */
 void* data ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_5__ guest ; 
 TYPE_4__ host ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int posix_memalign (void**,int,int) ; 
 TYPE_2__ ring ; 
 int ring_size ; 
 int /*<<< orphan*/  vring_init (TYPE_2__*,int,void*,int) ; 
 int vring_size (int,int) ; 

void alloc_ring(void)
{
	int ret;
	int i;
	void *p;

	ret = posix_memalign(&p, 0x1000, vring_size(ring_size, 0x1000));
	if (ret) {
		perror("Unable to allocate ring buffer.\n");
		exit(3);
	}
	memset(p, 0, vring_size(ring_size, 0x1000));
	vring_init(&ring, ring_size, p, 0x1000);

	guest.avail_idx = 0;
	guest.kicked_avail_idx = -1;
	guest.last_used_idx = 0;
#ifndef INORDER
	/* Put everything in free lists. */
	guest.free_head = 0;
#endif
	for (i = 0; i < ring_size - 1; i++)
		ring.desc[i].next = i + 1;
	host.used_idx = 0;
	host.called_used_idx = -1;
	guest.num_free = ring_size;
	data = malloc(ring_size * sizeof *data);
	if (!data) {
		perror("Unable to allocate data buffer.\n");
		exit(3);
	}
	memset(data, 0, ring_size * sizeof *data);
}