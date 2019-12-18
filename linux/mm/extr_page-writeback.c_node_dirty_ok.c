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
struct pglist_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 unsigned long node_dirty_limit (struct pglist_data*) ; 
 scalar_t__ node_page_state (struct pglist_data*,int /*<<< orphan*/ ) ; 

bool node_dirty_ok(struct pglist_data *pgdat)
{
	unsigned long limit = node_dirty_limit(pgdat);
	unsigned long nr_pages = 0;

	nr_pages += node_page_state(pgdat, NR_FILE_DIRTY);
	nr_pages += node_page_state(pgdat, NR_UNSTABLE_NFS);
	nr_pages += node_page_state(pgdat, NR_WRITEBACK);

	return nr_pages <= limit;
}