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
struct ring_buffer {int nr_pages; void* user_page; void** data_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_ORDER ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct ring_buffer*) ; 
 struct ring_buffer* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ order_base_2 (unsigned long) ; 
 void* perf_mmap_alloc_page (int) ; 
 int /*<<< orphan*/  ring_buffer_init (struct ring_buffer*,long,int) ; 

struct ring_buffer *rb_alloc(int nr_pages, long watermark, int cpu, int flags)
{
	struct ring_buffer *rb;
	unsigned long size;
	int i;

	size = sizeof(struct ring_buffer);
	size += nr_pages * sizeof(void *);

	if (order_base_2(size) >= PAGE_SHIFT+MAX_ORDER)
		goto fail;

	rb = kzalloc(size, GFP_KERNEL);
	if (!rb)
		goto fail;

	rb->user_page = perf_mmap_alloc_page(cpu);
	if (!rb->user_page)
		goto fail_user_page;

	for (i = 0; i < nr_pages; i++) {
		rb->data_pages[i] = perf_mmap_alloc_page(cpu);
		if (!rb->data_pages[i])
			goto fail_data_pages;
	}

	rb->nr_pages = nr_pages;

	ring_buffer_init(rb, watermark, flags);

	return rb;

fail_data_pages:
	for (i--; i >= 0; i--)
		free_page((unsigned long)rb->data_pages[i]);

	free_page((unsigned long)rb->user_page);

fail_user_page:
	kfree(rb);

fail:
	return NULL;
}