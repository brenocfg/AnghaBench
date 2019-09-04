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
struct ocfs2_info_freefrag_stats {unsigned int ffs_max; unsigned int ffs_min; unsigned int ffs_avg; int /*<<< orphan*/  ffs_free_chunks_real; } ;

/* Variables and functions */

__attribute__((used)) static void o2ffg_update_stats(struct ocfs2_info_freefrag_stats *stats,
			       unsigned int chunksize)
{
	if (chunksize > stats->ffs_max)
		stats->ffs_max = chunksize;

	if (chunksize < stats->ffs_min)
		stats->ffs_min = chunksize;

	stats->ffs_avg += chunksize;
	stats->ffs_free_chunks_real++;
}