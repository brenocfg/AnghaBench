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
struct ring_buffer_per_cpu {struct buffer_page* reader_page; struct buffer_page* commit_page; struct buffer_page* head_page; } ;
struct ring_buffer_iter {unsigned int head; struct buffer_page* head_page; struct ring_buffer_per_cpu* cpu_buffer; } ;
struct buffer_page {unsigned int read; } ;

/* Variables and functions */
 unsigned int rb_page_commit (struct buffer_page*) ; 

int ring_buffer_iter_empty(struct ring_buffer_iter *iter)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	struct buffer_page *reader;
	struct buffer_page *head_page;
	struct buffer_page *commit_page;
	unsigned commit;

	cpu_buffer = iter->cpu_buffer;

	/* Remember, trace recording is off when iterator is in use */
	reader = cpu_buffer->reader_page;
	head_page = cpu_buffer->head_page;
	commit_page = cpu_buffer->commit_page;
	commit = rb_page_commit(commit_page);

	return ((iter->head_page == commit_page && iter->head == commit) ||
		(iter->head_page == reader && commit_page == head_page &&
		 head_page->read == commit &&
		 iter->head == rb_page_commit(cpu_buffer->reader_page)));
}