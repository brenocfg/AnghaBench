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
struct ring_buffer_per_cpu {struct buffer_page* commit_page; } ;
struct ring_buffer_event {int dummy; } ;
struct buffer_page {void* page; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_inc_page (struct ring_buffer_per_cpu*,struct buffer_page**) ; 

__attribute__((used)) static inline void
rb_decrement_entry(struct ring_buffer_per_cpu *cpu_buffer,
		   struct ring_buffer_event *event)
{
	unsigned long addr = (unsigned long)event;
	struct buffer_page *bpage = cpu_buffer->commit_page;
	struct buffer_page *start;

	addr &= PAGE_MASK;

	/* Do the likely case first */
	if (likely(bpage->page == (void *)addr)) {
		local_dec(&bpage->entries);
		return;
	}

	/*
	 * Because the commit page may be on the reader page we
	 * start with the next page and check the end loop there.
	 */
	rb_inc_page(cpu_buffer, &bpage);
	start = bpage;
	do {
		if (bpage->page == (void *)addr) {
			local_dec(&bpage->entries);
			return;
		}
		rb_inc_page(cpu_buffer, &bpage);
	} while (bpage != start);

	/* commit not part of this buffer?? */
	RB_WARN_ON(cpu_buffer, 1);
}