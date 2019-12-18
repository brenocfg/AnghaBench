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
typedef  int /*<<< orphan*/  RowExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_COERCIONFORM_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  colnames ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  row_format ; 
 int /*<<< orphan*/  row_typeid ; 

__attribute__((used)) static bool
_equalRowExpr(const RowExpr *a, const RowExpr *b)
{
	COMPARE_NODE_FIELD(args);
	COMPARE_SCALAR_FIELD(row_typeid);
	COMPARE_COERCIONFORM_FIELD(row_format);
	COMPARE_NODE_FIELD(colnames);
	COMPARE_LOCATION_FIELD(location);

	return true;
}