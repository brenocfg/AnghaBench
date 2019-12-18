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
typedef  int /*<<< orphan*/  IndexVacuumInfo ;
typedef  int /*<<< orphan*/  IndexBulkDeleteResult ;
typedef  int /*<<< orphan*/  IndexBulkDeleteCallback ;
typedef  int /*<<< orphan*/  GistBulkDeleteResult ;

/* Variables and functions */
 int /*<<< orphan*/ * create_GistBulkDeleteResult () ; 
 int /*<<< orphan*/  gistvacuumscan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

IndexBulkDeleteResult *
gistbulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			   IndexBulkDeleteCallback callback, void *callback_state)
{
	GistBulkDeleteResult *gist_stats = (GistBulkDeleteResult *) stats;

	/* allocate stats if first time through, else re-use existing struct */
	if (gist_stats == NULL)
		gist_stats = create_GistBulkDeleteResult();

	gistvacuumscan(info, gist_stats, callback, callback_state);

	return (IndexBulkDeleteResult *) gist_stats;
}