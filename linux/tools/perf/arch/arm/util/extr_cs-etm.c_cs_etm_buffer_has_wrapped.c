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
typedef  size_t u64 ;

/* Variables and functions */

__attribute__((used)) static bool cs_etm_buffer_has_wrapped(unsigned char *buffer,
				      size_t buffer_size, u64 head)
{
	u64 i, watermark;
	u64 *buf = (u64 *)buffer;
	size_t buf_size = buffer_size;

	/*
	 * We want to look the very last 512 byte (chosen arbitrarily) in
	 * the ring buffer.
	 */
	watermark = buf_size - 512;

	/*
	 * @head is continuously increasing - if its value is equal or greater
	 * than the size of the ring buffer, it has wrapped around.
	 */
	if (head >= buffer_size)
		return true;

	/*
	 * The value of @head is somewhere within the size of the ring buffer.
	 * This can be that there hasn't been enough data to fill the ring
	 * buffer yet or the trace time was so long that @head has numerically
	 * wrapped around.  To find we need to check if we have data at the very
	 * end of the ring buffer.  We can reliably do this because mmap'ed
	 * pages are zeroed out and there is a fresh mapping with every new
	 * session.
	 */

	/* @head is less than 512 byte from the end of the ring buffer */
	if (head > watermark)
		watermark = head;

	/*
	 * Speed things up by using 64 bit transactions (see "u64 *buf" above)
	 */
	watermark >>= 3;
	buf_size >>= 3;

	/*
	 * If we find trace data at the end of the ring buffer, @head has
	 * been there and has numerically wrapped around at least once.
	 */
	for (i = watermark; i < buf_size; i++)
		if (buf[i])
			return true;

	return false;
}