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
struct TYPE_2__ {size_t value_size; } ;
struct bpf_queue_stack {size_t tail; size_t size; int /*<<< orphan*/  lock; TYPE_1__ map; int /*<<< orphan*/ * elements; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct bpf_queue_stack* bpf_queue_stack (struct bpf_map*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ queue_stack_map_is_empty (struct bpf_queue_stack*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __queue_map_get(struct bpf_map *map, void *value, bool delete)
{
	struct bpf_queue_stack *qs = bpf_queue_stack(map);
	unsigned long flags;
	int err = 0;
	void *ptr;

	raw_spin_lock_irqsave(&qs->lock, flags);

	if (queue_stack_map_is_empty(qs)) {
		memset(value, 0, qs->map.value_size);
		err = -ENOENT;
		goto out;
	}

	ptr = &qs->elements[qs->tail * qs->map.value_size];
	memcpy(value, ptr, qs->map.value_size);

	if (delete) {
		if (unlikely(++qs->tail >= qs->size))
			qs->tail = 0;
	}

out:
	raw_spin_unlock_irqrestore(&qs->lock, flags);
	return err;
}