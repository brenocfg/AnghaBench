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
struct resize_buf {size_t size; size_t capacity; scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 scalar_t__ realloc (scalar_t__,size_t) ; 

__attribute__((used)) static inline void resize_buf_resize(struct resize_buf *rb, size_t size)
{
	if (!rb->buf) {
		rb->buf = malloc(size);
		rb->size = size;
		rb->capacity = size;
	} else {
		if (rb->capacity < size) {
			size_t capx2 = rb->capacity * 2;
			size_t new_cap = capx2 > size ? capx2 : size;
			rb->buf = realloc(rb->buf, new_cap);
			rb->capacity = new_cap;
		}

		rb->size = size;
	}
}