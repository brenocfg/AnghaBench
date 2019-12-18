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
typedef  int /*<<< orphan*/  IndexFetchTableData ;
typedef  int /*<<< orphan*/  IndexFetchHeapData ;

/* Variables and functions */
 int /*<<< orphan*/  heapam_index_fetch_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
heapam_index_fetch_end(IndexFetchTableData *scan)
{
	IndexFetchHeapData *hscan = (IndexFetchHeapData *) scan;

	heapam_index_fetch_reset(scan);

	pfree(hscan);
}