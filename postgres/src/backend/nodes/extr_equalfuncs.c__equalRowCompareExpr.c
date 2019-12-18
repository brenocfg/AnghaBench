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
typedef  int /*<<< orphan*/  RowCompareExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inputcollids ; 
 int /*<<< orphan*/  largs ; 
 int /*<<< orphan*/  opfamilies ; 
 int /*<<< orphan*/  opnos ; 
 int /*<<< orphan*/  rargs ; 
 int /*<<< orphan*/  rctype ; 

__attribute__((used)) static bool
_equalRowCompareExpr(const RowCompareExpr *a, const RowCompareExpr *b)
{
	COMPARE_SCALAR_FIELD(rctype);
	COMPARE_NODE_FIELD(opnos);
	COMPARE_NODE_FIELD(opfamilies);
	COMPARE_NODE_FIELD(inputcollids);
	COMPARE_NODE_FIELD(largs);
	COMPARE_NODE_FIELD(rargs);

	return true;
}