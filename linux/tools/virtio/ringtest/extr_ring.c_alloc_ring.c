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
struct desc {int index; } ;
struct TYPE_4__ {int kicked_avail_idx; int num_free; scalar_t__ last_used_idx; scalar_t__ avail_idx; } ;
struct TYPE_3__ {int called_used_idx; scalar_t__ used_idx; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 void* data ; 
 void* event ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_2__ guest ; 
 TYPE_1__ host ; 
 int /*<<< orphan*/  perror (char*) ; 
 int posix_memalign (void**,int,int) ; 
 struct desc* ring ; 
 int ring_size ; 

void alloc_ring(void)
{
	int ret;
	int i;

	ret = posix_memalign((void **)&ring, 0x1000, ring_size * sizeof *ring);
	if (ret) {
		perror("Unable to allocate ring buffer.\n");
		exit(3);
	}
	event = calloc(1, sizeof(*event));
	if (!event) {
		perror("Unable to allocate event buffer.\n");
		exit(3);
	}
	guest.avail_idx = 0;
	guest.kicked_avail_idx = -1;
	guest.last_used_idx = 0;
	host.used_idx = 0;
	host.called_used_idx = -1;
	for (i = 0; i < ring_size; ++i) {
		struct desc desc = {
			.index = i,
		};
		ring[i] = desc;
	}
	guest.num_free = ring_size;
	data = calloc(ring_size, sizeof(*data));
	if (!data) {
		perror("Unable to allocate data buffer.\n");
		exit(3);
	}
}