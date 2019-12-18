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
typedef  int /*<<< orphan*/  ArrayExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_collid ; 
 int /*<<< orphan*/  array_typeid ; 
 int /*<<< orphan*/  element_typeid ; 
 int /*<<< orphan*/  elements ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  multidims ; 

__attribute__((used)) static bool
_equalArrayExpr(const ArrayExpr *a, const ArrayExpr *b)
{
	COMPARE_SCALAR_FIELD(array_typeid);
	COMPARE_SCALAR_FIELD(array_collid);
	COMPARE_SCALAR_FIELD(element_typeid);
	COMPARE_NODE_FIELD(elements);
	COMPARE_SCALAR_FIELD(multidims);
	COMPARE_LOCATION_FIELD(location);

	return true;
}