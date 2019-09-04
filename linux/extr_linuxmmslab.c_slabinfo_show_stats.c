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
struct seq_file {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */

void slabinfo_show_stats(struct seq_file *m, struct kmem_cache *cachep)
{
#if STATS
	{			/* node stats */
		unsigned long high = cachep->high_mark;
		unsigned long allocs = cachep->num_allocations;
		unsigned long grown = cachep->grown;
		unsigned long reaped = cachep->reaped;
		unsigned long errors = cachep->errors;
		unsigned long max_freeable = cachep->max_freeable;
		unsigned long node_allocs = cachep->node_allocs;
		unsigned long node_frees = cachep->node_frees;
		unsigned long overflows = cachep->node_overflow;

		seq_printf(m, " : globalstat %7lu %6lu %5lu %4lu %4lu %4lu %4lu %4lu %4lu",
			   allocs, high, grown,
			   reaped, errors, max_freeable, node_allocs,
			   node_frees, overflows);
	}
	/* cpu stats */
	{
		unsigned long allochit = atomic_read(&cachep->allochit);
		unsigned long allocmiss = atomic_read(&cachep->allocmiss);
		unsigned long freehit = atomic_read(&cachep->freehit);
		unsigned long freemiss = atomic_read(&cachep->freemiss);

		seq_printf(m, " : cpustat %6lu %6lu %6lu %6lu",
			   allochit, allocmiss, freehit, freemiss);
	}
#endif
}