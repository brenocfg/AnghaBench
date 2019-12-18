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
struct slabinfo {int alloc_slab; unsigned long alloc_fastpath; unsigned long alloc_slowpath; unsigned long free_fastpath; unsigned long free_slowpath; int free_slab; int deactivate_to_head; int deactivate_to_tail; int free_add_partial; int alloc_from_partial; int free_remove_partial; int cpu_partial_alloc; int cpu_partial_free; int deactivate_remote_frees; int free_frozen; long cpuslab_flush; unsigned long deactivate_full; unsigned long deactivate_empty; unsigned long deactivate_bypass; unsigned long alloc_refill; unsigned long alloc_node_mismatch; unsigned long cmpxchg_double_fail; int cmpxchg_double_cpu_fail; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void slab_stats(struct slabinfo *s)
{
	unsigned long total_alloc;
	unsigned long total_free;
	unsigned long total;

	if (!s->alloc_slab)
		return;

	total_alloc = s->alloc_fastpath + s->alloc_slowpath;
	total_free = s->free_fastpath + s->free_slowpath;

	if (!total_alloc)
		return;

	printf("\n");
	printf("Slab Perf Counter       Alloc     Free %%Al %%Fr\n");
	printf("--------------------------------------------------\n");
	printf("Fastpath             %8lu %8lu %3lu %3lu\n",
		s->alloc_fastpath, s->free_fastpath,
		s->alloc_fastpath * 100 / total_alloc,
		total_free ? s->free_fastpath * 100 / total_free : 0);
	printf("Slowpath             %8lu %8lu %3lu %3lu\n",
		total_alloc - s->alloc_fastpath, s->free_slowpath,
		(total_alloc - s->alloc_fastpath) * 100 / total_alloc,
		total_free ? s->free_slowpath * 100 / total_free : 0);
	printf("Page Alloc           %8lu %8lu %3lu %3lu\n",
		s->alloc_slab, s->free_slab,
		s->alloc_slab * 100 / total_alloc,
		total_free ? s->free_slab * 100 / total_free : 0);
	printf("Add partial          %8lu %8lu %3lu %3lu\n",
		s->deactivate_to_head + s->deactivate_to_tail,
		s->free_add_partial,
		(s->deactivate_to_head + s->deactivate_to_tail) * 100 / total_alloc,
		total_free ? s->free_add_partial * 100 / total_free : 0);
	printf("Remove partial       %8lu %8lu %3lu %3lu\n",
		s->alloc_from_partial, s->free_remove_partial,
		s->alloc_from_partial * 100 / total_alloc,
		total_free ? s->free_remove_partial * 100 / total_free : 0);

	printf("Cpu partial list     %8lu %8lu %3lu %3lu\n",
		s->cpu_partial_alloc, s->cpu_partial_free,
		s->cpu_partial_alloc * 100 / total_alloc,
		total_free ? s->cpu_partial_free * 100 / total_free : 0);

	printf("RemoteObj/SlabFrozen %8lu %8lu %3lu %3lu\n",
		s->deactivate_remote_frees, s->free_frozen,
		s->deactivate_remote_frees * 100 / total_alloc,
		total_free ? s->free_frozen * 100 / total_free : 0);

	printf("Total                %8lu %8lu\n\n", total_alloc, total_free);

	if (s->cpuslab_flush)
		printf("Flushes %8lu\n", s->cpuslab_flush);

	total = s->deactivate_full + s->deactivate_empty +
			s->deactivate_to_head + s->deactivate_to_tail + s->deactivate_bypass;

	if (total) {
		printf("\nSlab Deactivation             Occurrences %%\n");
		printf("-------------------------------------------------\n");
		printf("Slab full                     %7lu  %3lu%%\n",
			s->deactivate_full, (s->deactivate_full * 100) / total);
		printf("Slab empty                    %7lu  %3lu%%\n",
			s->deactivate_empty, (s->deactivate_empty * 100) / total);
		printf("Moved to head of partial list %7lu  %3lu%%\n",
			s->deactivate_to_head, (s->deactivate_to_head * 100) / total);
		printf("Moved to tail of partial list %7lu  %3lu%%\n",
			s->deactivate_to_tail, (s->deactivate_to_tail * 100) / total);
		printf("Deactivation bypass           %7lu  %3lu%%\n",
			s->deactivate_bypass, (s->deactivate_bypass * 100) / total);
		printf("Refilled from foreign frees   %7lu  %3lu%%\n",
			s->alloc_refill, (s->alloc_refill * 100) / total);
		printf("Node mismatch                 %7lu  %3lu%%\n",
			s->alloc_node_mismatch, (s->alloc_node_mismatch * 100) / total);
	}

	if (s->cmpxchg_double_fail || s->cmpxchg_double_cpu_fail) {
		printf("\nCmpxchg_double Looping\n------------------------\n");
		printf("Locked Cmpxchg Double redos   %lu\nUnlocked Cmpxchg Double redos %lu\n",
			s->cmpxchg_double_fail, s->cmpxchg_double_cpu_fail);
	}
}