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
typedef  int /*<<< orphan*/  FuncExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_COERCIONFORM_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  funccollid ; 
 int /*<<< orphan*/  funcformat ; 
 int /*<<< orphan*/  funcid ; 
 int /*<<< orphan*/  funcresulttype ; 
 int /*<<< orphan*/  funcretset ; 
 int /*<<< orphan*/  funcvariadic ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static bool
_equalFuncExpr(const FuncExpr *a, const FuncExpr *b)
{
	COMPARE_SCALAR_FIELD(funcid);
	COMPARE_SCALAR_FIELD(funcresulttype);
	COMPARE_SCALAR_FIELD(funcretset);
	COMPARE_SCALAR_FIELD(funcvariadic);
	COMPARE_COERCIONFORM_FIELD(funcformat);
	COMPARE_SCALAR_FIELD(funccollid);
	COMPARE_SCALAR_FIELD(inputcollid);
	COMPARE_NODE_FIELD(args);
	COMPARE_LOCATION_FIELD(location);

	return true;
}