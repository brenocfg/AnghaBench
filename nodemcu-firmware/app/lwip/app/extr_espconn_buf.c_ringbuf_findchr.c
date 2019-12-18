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
struct ringbuf_t {int /*<<< orphan*/ * buf; int /*<<< orphan*/ * tail; } ;

/* Variables and functions */
 size_t LWIP_MIN (int,size_t) ; 
 int /*<<< orphan*/  lwIP_ASSERT (int) ; 
 scalar_t__ memchr (int /*<<< orphan*/  const*,int,size_t) ; 
 int ringbuf_buffer_size (struct ringbuf_t const*) ; 
 size_t ringbuf_bytes_used (struct ringbuf_t const*) ; 
 int /*<<< orphan*/ * ringbuf_end (struct ringbuf_t const*) ; 

size_t ringbuf_findchr(const struct ringbuf_t *rb, int c, size_t offset)
{
	const uint8_t *bufend = ringbuf_end(rb);
	size_t bytes_used = ringbuf_bytes_used(rb);
	if (offset >= bytes_used)
		return bytes_used;

	const uint8_t *start = rb ->buf + (((rb->tail - rb->buf) + offset) % ringbuf_buffer_size(rb));
	lwIP_ASSERT(bufend > start);
	size_t n = LWIP_MIN(bufend - start, bytes_used - offset);
	const uint8_t *found = (const uint8_t *)memchr(start, c, n);
	if (found)
		return offset + (found - start);
	else
		return ringbuf_findchr(rb, c, offset + n);
}