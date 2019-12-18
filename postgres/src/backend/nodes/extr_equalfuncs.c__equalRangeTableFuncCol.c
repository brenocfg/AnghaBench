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
typedef  int /*<<< orphan*/  RangeTableFuncCol ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coldefexpr ; 
 int /*<<< orphan*/  colexpr ; 
 int /*<<< orphan*/  colname ; 
 int /*<<< orphan*/  for_ordinality ; 
 int /*<<< orphan*/  is_not_null ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  typeName ; 

__attribute__((used)) static bool
_equalRangeTableFuncCol(const RangeTableFuncCol *a, const RangeTableFuncCol *b)
{
	COMPARE_STRING_FIELD(colname);
	COMPARE_NODE_FIELD(typeName);
	COMPARE_SCALAR_FIELD(for_ordinality);
	COMPARE_SCALAR_FIELD(is_not_null);
	COMPARE_NODE_FIELD(colexpr);
	COMPARE_NODE_FIELD(coldefexpr);
	COMPARE_LOCATION_FIELD(location);

	return true;
}