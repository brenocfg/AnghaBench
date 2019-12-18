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
typedef  int /*<<< orphan*/  FuncCall ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_distinct ; 
 int /*<<< orphan*/  agg_filter ; 
 int /*<<< orphan*/  agg_order ; 
 int /*<<< orphan*/  agg_star ; 
 int /*<<< orphan*/  agg_within_group ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  func_variadic ; 
 int /*<<< orphan*/  funcname ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  over ; 

__attribute__((used)) static bool
_equalFuncCall(const FuncCall *a, const FuncCall *b)
{
	COMPARE_NODE_FIELD(funcname);
	COMPARE_NODE_FIELD(args);
	COMPARE_NODE_FIELD(agg_order);
	COMPARE_NODE_FIELD(agg_filter);
	COMPARE_SCALAR_FIELD(agg_within_group);
	COMPARE_SCALAR_FIELD(agg_star);
	COMPARE_SCALAR_FIELD(agg_distinct);
	COMPARE_SCALAR_FIELD(func_variadic);
	COMPARE_NODE_FIELD(over);
	COMPARE_LOCATION_FIELD(location);

	return true;
}