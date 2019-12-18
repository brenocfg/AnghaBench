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
typedef  int /*<<< orphan*/  SortBy ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  node ; 
 int /*<<< orphan*/  sortby_dir ; 
 int /*<<< orphan*/  sortby_nulls ; 
 int /*<<< orphan*/  useOp ; 

__attribute__((used)) static bool
_equalSortBy(const SortBy *a, const SortBy *b)
{
	COMPARE_NODE_FIELD(node);
	COMPARE_SCALAR_FIELD(sortby_dir);
	COMPARE_SCALAR_FIELD(sortby_nulls);
	COMPARE_NODE_FIELD(useOp);
	COMPARE_LOCATION_FIELD(location);

	return true;
}