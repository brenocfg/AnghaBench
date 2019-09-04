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
struct pcpu_chunk {scalar_t__ data; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_pages (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_base_2 (int const) ; 
 int /*<<< orphan*/  pcpu_free_chunk (struct pcpu_chunk*) ; 
 int* pcpu_group_sizes ; 
 int /*<<< orphan*/  pcpu_stats_chunk_dealloc () ; 
 int /*<<< orphan*/  trace_percpu_destroy_chunk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcpu_destroy_chunk(struct pcpu_chunk *chunk)
{
	const int nr_pages = pcpu_group_sizes[0] >> PAGE_SHIFT;

	if (!chunk)
		return;

	pcpu_stats_chunk_dealloc();
	trace_percpu_destroy_chunk(chunk->base_addr);

	if (chunk->data)
		__free_pages(chunk->data, order_base_2(nr_pages));
	pcpu_free_chunk(chunk);
}