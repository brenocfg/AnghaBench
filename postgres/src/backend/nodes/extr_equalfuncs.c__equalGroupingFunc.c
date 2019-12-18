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
typedef  int /*<<< orphan*/  GroupingFunc ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agglevelsup ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static bool
_equalGroupingFunc(const GroupingFunc *a, const GroupingFunc *b)
{
	COMPARE_NODE_FIELD(args);

	/*
	 * We must not compare the refs or cols field
	 */

	COMPARE_SCALAR_FIELD(agglevelsup);
	COMPARE_LOCATION_FIELD(location);

	return true;
}