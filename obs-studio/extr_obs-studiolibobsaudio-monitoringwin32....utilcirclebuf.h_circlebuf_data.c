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
typedef  void uint8_t ;
struct circlebuf {size_t start_pos; size_t size; size_t capacity; scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static inline void *circlebuf_data(struct circlebuf *cb, size_t idx)
{
	uint8_t *ptr = (uint8_t*)cb->data;
	size_t offset = cb->start_pos + idx;

	if (idx >= cb->size)
		return NULL;

	if (offset >= cb->capacity)
		offset -= cb->capacity;

	return ptr + offset;
}