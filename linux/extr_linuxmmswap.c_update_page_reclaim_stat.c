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
struct zone_reclaim_stat {int /*<<< orphan*/ * recent_rotated; int /*<<< orphan*/ * recent_scanned; } ;
struct lruvec {struct zone_reclaim_stat reclaim_stat; } ;

/* Variables and functions */

__attribute__((used)) static void update_page_reclaim_stat(struct lruvec *lruvec,
				     int file, int rotated)
{
	struct zone_reclaim_stat *reclaim_stat = &lruvec->reclaim_stat;

	reclaim_stat->recent_scanned[file]++;
	if (rotated)
		reclaim_stat->recent_rotated[file]++;
}