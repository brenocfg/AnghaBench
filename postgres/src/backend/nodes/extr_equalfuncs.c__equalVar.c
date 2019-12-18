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
typedef  int /*<<< orphan*/  Var ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  varattno ; 
 int /*<<< orphan*/  varcollid ; 
 int /*<<< orphan*/  varlevelsup ; 
 int /*<<< orphan*/  varno ; 
 int /*<<< orphan*/  varnoold ; 
 int /*<<< orphan*/  varoattno ; 
 int /*<<< orphan*/  vartype ; 
 int /*<<< orphan*/  vartypmod ; 

__attribute__((used)) static bool
_equalVar(const Var *a, const Var *b)
{
	COMPARE_SCALAR_FIELD(varno);
	COMPARE_SCALAR_FIELD(varattno);
	COMPARE_SCALAR_FIELD(vartype);
	COMPARE_SCALAR_FIELD(vartypmod);
	COMPARE_SCALAR_FIELD(varcollid);
	COMPARE_SCALAR_FIELD(varlevelsup);
	COMPARE_SCALAR_FIELD(varnoold);
	COMPARE_SCALAR_FIELD(varoattno);
	COMPARE_LOCATION_FIELD(location);

	return true;
}