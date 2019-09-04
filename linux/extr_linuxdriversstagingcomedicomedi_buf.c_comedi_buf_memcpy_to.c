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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_async {unsigned int buf_write_ptr; unsigned int prealloc_bufsz; scalar_t__ prealloc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,unsigned int) ; 

__attribute__((used)) static void comedi_buf_memcpy_to(struct comedi_subdevice *s,
				 const void *data, unsigned int num_bytes)
{
	struct comedi_async *async = s->async;
	unsigned int write_ptr = async->buf_write_ptr;

	while (num_bytes) {
		unsigned int block_size;

		if (write_ptr + num_bytes > async->prealloc_bufsz)
			block_size = async->prealloc_bufsz - write_ptr;
		else
			block_size = num_bytes;

		memcpy(async->prealloc_buf + write_ptr, data, block_size);

		data += block_size;
		num_bytes -= block_size;

		write_ptr = 0;
	}
}