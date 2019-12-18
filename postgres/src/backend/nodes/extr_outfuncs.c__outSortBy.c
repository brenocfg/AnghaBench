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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  SortBy ;

/* Variables and functions */
 int /*<<< orphan*/  SortByDir ; 
 int /*<<< orphan*/  SortByNulls ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  sortby_dir ; 
 int /*<<< orphan*/  sortby_nulls ; 
 int /*<<< orphan*/  const* useOp ; 

__attribute__((used)) static void
_outSortBy(StringInfo str, const SortBy *node)
{
	WRITE_NODE_TYPE("SORTBY");

	WRITE_NODE_FIELD(node);
	WRITE_ENUM_FIELD(sortby_dir, SortByDir);
	WRITE_ENUM_FIELD(sortby_nulls, SortByNulls);
	WRITE_NODE_FIELD(useOp);
	WRITE_LOCATION_FIELD(location);
}