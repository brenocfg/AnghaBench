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
struct pcpu_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_cache_vunmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_chunk_addr (struct pcpu_chunk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcpu_high_unit_cpu ; 
 int /*<<< orphan*/  pcpu_low_unit_cpu ; 

__attribute__((used)) static void pcpu_pre_unmap_flush(struct pcpu_chunk *chunk,
				 int page_start, int page_end)
{
	flush_cache_vunmap(
		pcpu_chunk_addr(chunk, pcpu_low_unit_cpu, page_start),
		pcpu_chunk_addr(chunk, pcpu_high_unit_cpu, page_end));
}