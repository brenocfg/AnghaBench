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
struct ring_buffer {TYPE_1__** buffers; int /*<<< orphan*/  cpumask; } ;
struct TYPE_2__ {unsigned long nr_pages; } ;

/* Variables and functions */
 unsigned long BUF_PAGE_SIZE ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 

unsigned long ring_buffer_size(struct ring_buffer *buffer, int cpu)
{
	/*
	 * Earlier, this method returned
	 *	BUF_PAGE_SIZE * buffer->nr_pages
	 * Since the nr_pages field is now removed, we have converted this to
	 * return the per cpu buffer value.
	 */
	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return 0;

	return BUF_PAGE_SIZE * buffer->buffers[cpu]->nr_pages;
}