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
struct ring_buffer {unsigned long nr_pages; int /*<<< orphan*/ * data_pages; int /*<<< orphan*/  user_page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *
__perf_mmap_to_page(struct ring_buffer *rb, unsigned long pgoff)
{
	if (pgoff > rb->nr_pages)
		return NULL;

	if (pgoff == 0)
		return virt_to_page(rb->user_page);

	return virt_to_page(rb->data_pages[pgoff - 1]);
}