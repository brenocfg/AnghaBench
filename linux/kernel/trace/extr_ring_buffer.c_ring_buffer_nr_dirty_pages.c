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
struct ring_buffer {TYPE_1__** buffers; } ;
struct TYPE_2__ {int /*<<< orphan*/  pages_touched; int /*<<< orphan*/  pages_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 size_t local_read (int /*<<< orphan*/ *) ; 

size_t ring_buffer_nr_dirty_pages(struct ring_buffer *buffer, int cpu)
{
	size_t read;
	size_t cnt;

	read = local_read(&buffer->buffers[cpu]->pages_read);
	cnt = local_read(&buffer->buffers[cpu]->pages_touched);
	/* The reader can read an empty page, but not more than that */
	if (cnt < read) {
		WARN_ON_ONCE(read > cnt + 1);
		return 0;
	}

	return cnt - read;
}