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
typedef  int /*<<< orphan*/  RangeTableSample ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  method ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  repeatable ; 

__attribute__((used)) static bool
_equalRangeTableSample(const RangeTableSample *a, const RangeTableSample *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(method);
	COMPARE_NODE_FIELD(args);
	COMPARE_NODE_FIELD(repeatable);
	COMPARE_LOCATION_FIELD(location);

	return true;
}