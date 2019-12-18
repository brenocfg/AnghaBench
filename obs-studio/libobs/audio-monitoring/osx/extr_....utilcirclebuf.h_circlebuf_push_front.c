#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void const uint8_t ;
struct circlebuf {size_t size; size_t start_pos; void const* data; size_t capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_ensure_capacity (struct circlebuf*) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,size_t) ; 

__attribute__((used)) static inline void circlebuf_push_front(struct circlebuf *cb, const void *data,
					size_t size)
{
	cb->size += size;
	circlebuf_ensure_capacity(cb);

	if (cb->start_pos < size) {
		size_t back_size = size - cb->start_pos;

		if (cb->start_pos)
			memcpy(cb->data, (uint8_t *)data + back_size,
			       cb->start_pos);

		cb->start_pos = cb->capacity - back_size;
		memcpy((uint8_t *)cb->data + cb->start_pos, data, back_size);
	} else {
		cb->start_pos -= size;
		memcpy((uint8_t *)cb->data + cb->start_pos, data, size);
	}
}