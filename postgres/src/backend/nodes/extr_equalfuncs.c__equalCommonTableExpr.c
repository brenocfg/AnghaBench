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
typedef  int /*<<< orphan*/  CommonTableExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aliascolnames ; 
 int /*<<< orphan*/  ctecolcollations ; 
 int /*<<< orphan*/  ctecolnames ; 
 int /*<<< orphan*/  ctecoltypes ; 
 int /*<<< orphan*/  ctecoltypmods ; 
 int /*<<< orphan*/  ctematerialized ; 
 int /*<<< orphan*/  ctename ; 
 int /*<<< orphan*/  ctequery ; 
 int /*<<< orphan*/  cterecursive ; 
 int /*<<< orphan*/  cterefcount ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static bool
_equalCommonTableExpr(const CommonTableExpr *a, const CommonTableExpr *b)
{
	COMPARE_STRING_FIELD(ctename);
	COMPARE_NODE_FIELD(aliascolnames);
	COMPARE_SCALAR_FIELD(ctematerialized);
	COMPARE_NODE_FIELD(ctequery);
	COMPARE_LOCATION_FIELD(location);
	COMPARE_SCALAR_FIELD(cterecursive);
	COMPARE_SCALAR_FIELD(cterefcount);
	COMPARE_NODE_FIELD(ctecolnames);
	COMPARE_NODE_FIELD(ctecoltypes);
	COMPARE_NODE_FIELD(ctecoltypmods);
	COMPARE_NODE_FIELD(ctecolcollations);

	return true;
}