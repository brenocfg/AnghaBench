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

/* Variables and functions */

__attribute__((used)) static IndexBulkDeleteResult *
divacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	/* Index has not been modified, so returning NULL is fine */
	return NULL;
}