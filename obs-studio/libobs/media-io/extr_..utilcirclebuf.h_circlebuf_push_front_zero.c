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
typedef  int /*<<< orphan*/  uint8_t ;
struct circlebuf {size_t size; size_t start_pos; size_t capacity; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_ensure_capacity (struct circlebuf*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void circlebuf_push_front_zero(struct circlebuf *cb, size_t size)
{
	cb->size += size;
	circlebuf_ensure_capacity(cb);

	if (cb->start_pos < size) {
		size_t back_size = size - cb->start_pos;

		if (cb->start_pos)
			memset(cb->data, 0, cb->start_pos);

		cb->start_pos = cb->capacity - back_size;
		memset((uint8_t *)cb->data + cb->start_pos, 0, back_size);
	} else {
		cb->start_pos -= size;
		memset((uint8_t *)cb->data + cb->start_pos, 0, size);
	}
}