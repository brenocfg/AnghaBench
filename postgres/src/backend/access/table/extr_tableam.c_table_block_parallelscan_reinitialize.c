#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  phs_nallocated; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ParallelTableScanDesc ;
typedef  TYPE_1__* ParallelBlockTableScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  pg_atomic_write_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
table_block_parallelscan_reinitialize(Relation rel, ParallelTableScanDesc pscan)
{
	ParallelBlockTableScanDesc bpscan = (ParallelBlockTableScanDesc) pscan;

	pg_atomic_write_u64(&bpscan->phs_nallocated, 0);
}