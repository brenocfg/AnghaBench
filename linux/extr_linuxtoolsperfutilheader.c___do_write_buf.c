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
struct perf_event_header {int dummy; } ;
struct feat_fd {size_t size; size_t offset; void* buf; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 size_t min (size_t const,size_t) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static int __do_write_buf(struct feat_fd *ff,  const void *buf, size_t size)
{
	/* struct perf_event_header::size is u16 */
	const size_t max_size = 0xffff - sizeof(struct perf_event_header);
	size_t new_size = ff->size;
	void *addr;

	if (size + ff->offset > max_size)
		return -E2BIG;

	while (size > (new_size - ff->offset))
		new_size <<= 1;
	new_size = min(max_size, new_size);

	if (ff->size < new_size) {
		addr = realloc(ff->buf, new_size);
		if (!addr)
			return -ENOMEM;
		ff->buf = addr;
		ff->size = new_size;
	}

	memcpy(ff->buf + ff->offset, buf, size);
	ff->offset += size;

	return 0;
}