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
struct zone {int dummy; } ;
struct scan_control {int /*<<< orphan*/  reclaim_idx; int /*<<< orphan*/  order; } ;
typedef  enum compact_result { ____Placeholder_compact_result } compact_result ;

/* Variables and functions */
 int COMPACT_SKIPPED ; 
 int COMPACT_SUCCESS ; 
 unsigned long compact_gap (int /*<<< orphan*/ ) ; 
 int compaction_suitable (struct zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long high_wmark_pages (struct zone*) ; 
 int zone_watermark_ok_safe (struct zone*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool compaction_ready(struct zone *zone, struct scan_control *sc)
{
	unsigned long watermark;
	enum compact_result suitable;

	suitable = compaction_suitable(zone, sc->order, 0, sc->reclaim_idx);
	if (suitable == COMPACT_SUCCESS)
		/* Allocation should succeed already. Don't reclaim. */
		return true;
	if (suitable == COMPACT_SKIPPED)
		/* Compaction cannot yet proceed. Do reclaim. */
		return false;

	/*
	 * Compaction is already possible, but it takes time to run and there
	 * are potentially other callers using the pages just freed. So proceed
	 * with reclaim to make a buffer of free pages available to give
	 * compaction a reasonable chance of completing and allocating the page.
	 * Note that we won't actually reclaim the whole buffer in one attempt
	 * as the target watermark in should_continue_reclaim() is lower. But if
	 * we are already above the high+gap watermark, don't reclaim at all.
	 */
	watermark = high_wmark_pages(zone) + compact_gap(sc->order);

	return zone_watermark_ok_safe(zone, 0, watermark, sc->reclaim_idx);
}