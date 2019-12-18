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
struct circlebuf {size_t size; size_t capacity; void const* data; scalar_t__ start_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_upsize (struct circlebuf*,size_t) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,size_t) ; 

__attribute__((used)) static inline void circlebuf_place(struct circlebuf *cb, size_t position,
				   const void *data, size_t size)
{
	size_t end_point = position + size;
	size_t data_end_pos;

	if (end_point > cb->size)
		circlebuf_upsize(cb, end_point);

	position += cb->start_pos;
	if (position >= cb->capacity)
		position -= cb->capacity;

	data_end_pos = position + size;
	if (data_end_pos > cb->capacity) {
		size_t back_size = data_end_pos - cb->capacity;
		size_t loop_size = size - back_size;

		if (back_size)
			memcpy((uint8_t *)cb->data + position, data, loop_size);
		memcpy(cb->data, (uint8_t *)data + loop_size, back_size);
	} else {
		memcpy((uint8_t *)cb->data + position, data, size);
	}
}