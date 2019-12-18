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
typedef  int /*<<< orphan*/  MinMaxExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  minmaxcollid ; 
 int /*<<< orphan*/  minmaxtype ; 
 int /*<<< orphan*/  op ; 

__attribute__((used)) static bool
_equalMinMaxExpr(const MinMaxExpr *a, const MinMaxExpr *b)
{
	COMPARE_SCALAR_FIELD(minmaxtype);
	COMPARE_SCALAR_FIELD(minmaxcollid);
	COMPARE_SCALAR_FIELD(inputcollid);
	COMPARE_SCALAR_FIELD(op);
	COMPARE_NODE_FIELD(args);
	COMPARE_LOCATION_FIELD(location);

	return true;
}