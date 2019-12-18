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
typedef  int u64 ;
struct TYPE_2__ {size_t value_size; } ;
struct bpf_queue_stack {size_t tail; size_t size; size_t head; int /*<<< orphan*/  lock; TYPE_1__ map; int /*<<< orphan*/ * elements; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int BPF_EXIST ; 
 int BPF_NOEXIST ; 
 int E2BIG ; 
 int EINVAL ; 
 struct bpf_queue_stack* bpf_queue_stack (struct bpf_map*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 scalar_t__ queue_stack_map_is_full (struct bpf_queue_stack*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int queue_stack_map_push_elem(struct bpf_map *map, void *value,
				     u64 flags)
{
	struct bpf_queue_stack *qs = bpf_queue_stack(map);
	unsigned long irq_flags;
	int err = 0;
	void *dst;

	/* BPF_EXIST is used to force making room for a new element in case the
	 * map is full
	 */
	bool replace = (flags & BPF_EXIST);

	/* Check supported flags for queue and stack maps */
	if (flags & BPF_NOEXIST || flags > BPF_EXIST)
		return -EINVAL;

	raw_spin_lock_irqsave(&qs->lock, irq_flags);

	if (queue_stack_map_is_full(qs)) {
		if (!replace) {
			err = -E2BIG;
			goto out;
		}
		/* advance tail pointer to overwrite oldest element */
		if (unlikely(++qs->tail >= qs->size))
			qs->tail = 0;
	}

	dst = &qs->elements[qs->head * qs->map.value_size];
	memcpy(dst, value, qs->map.value_size);

	if (unlikely(++qs->head >= qs->size))
		qs->head = 0;

out:
	raw_spin_unlock_irqrestore(&qs->lock, irq_flags);
	return err;
}