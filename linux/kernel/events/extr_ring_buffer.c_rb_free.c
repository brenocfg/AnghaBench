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
struct ring_buffer {int nr_pages; scalar_t__* data_pages; scalar_t__ user_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ring_buffer*) ; 
 int /*<<< orphan*/  perf_mmap_free_page (unsigned long) ; 

void rb_free(struct ring_buffer *rb)
{
	int i;

	perf_mmap_free_page((unsigned long)rb->user_page);
	for (i = 0; i < rb->nr_pages; i++)
		perf_mmap_free_page((unsigned long)rb->data_pages[i]);
	kfree(rb);
}