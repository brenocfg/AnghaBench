#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ num_index_tuples; } ;
struct TYPE_12__ {TYPE_1__ stats; int /*<<< orphan*/ * empty_leaf_set; int /*<<< orphan*/ * internal_page_set; int /*<<< orphan*/ * page_set_context; } ;
struct TYPE_11__ {scalar_t__ num_heap_tuples; int /*<<< orphan*/  estimated_count; scalar_t__ analyze_only; } ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexBulkDeleteResult ;
typedef  TYPE_3__ GistBulkDeleteResult ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 TYPE_3__* create_GistBulkDeleteResult () ; 
 int /*<<< orphan*/  gistvacuum_delete_empty_pages (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gistvacuumscan (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

IndexBulkDeleteResult *
gistvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	GistBulkDeleteResult *gist_stats = (GistBulkDeleteResult *) stats;

	/* No-op in ANALYZE ONLY mode */
	if (info->analyze_only)
		return stats;

	/*
	 * If gistbulkdelete was called, we need not do anything, just return the
	 * stats from the latest gistbulkdelete call.  If it wasn't called, we
	 * still need to do a pass over the index, to obtain index statistics.
	 */
	if (gist_stats == NULL)
	{
		gist_stats = create_GistBulkDeleteResult();
		gistvacuumscan(info, gist_stats, NULL, NULL);
	}

	/*
	 * If we saw any empty pages, try to unlink them from the tree so that
	 * they can be reused.
	 */
	gistvacuum_delete_empty_pages(info, gist_stats);

	/* we don't need the internal and empty page sets anymore */
	MemoryContextDelete(gist_stats->page_set_context);
	gist_stats->page_set_context = NULL;
	gist_stats->internal_page_set = NULL;
	gist_stats->empty_leaf_set = NULL;

	/*
	 * It's quite possible for us to be fooled by concurrent page splits into
	 * double-counting some index tuples, so disbelieve any total that exceeds
	 * the underlying heap's count ... if we know that accurately.  Otherwise
	 * this might just make matters worse.
	 */
	if (!info->estimated_count)
	{
		if (gist_stats->stats.num_index_tuples > info->num_heap_tuples)
			gist_stats->stats.num_index_tuples = info->num_heap_tuples;
	}

	return (IndexBulkDeleteResult *) gist_stats;
}