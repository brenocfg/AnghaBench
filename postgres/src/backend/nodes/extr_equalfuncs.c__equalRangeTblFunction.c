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
typedef  int /*<<< orphan*/  RangeTblFunction ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funccolcollations ; 
 int /*<<< orphan*/  funccolcount ; 
 int /*<<< orphan*/  funccolnames ; 
 int /*<<< orphan*/  funccoltypes ; 
 int /*<<< orphan*/  funccoltypmods ; 
 int /*<<< orphan*/  funcexpr ; 
 int /*<<< orphan*/  funcparams ; 

__attribute__((used)) static bool
_equalRangeTblFunction(const RangeTblFunction *a, const RangeTblFunction *b)
{
	COMPARE_NODE_FIELD(funcexpr);
	COMPARE_SCALAR_FIELD(funccolcount);
	COMPARE_NODE_FIELD(funccolnames);
	COMPARE_NODE_FIELD(funccoltypes);
	COMPARE_NODE_FIELD(funccoltypmods);
	COMPARE_NODE_FIELD(funccolcollations);
	COMPARE_BITMAPSET_FIELD(funcparams);

	return true;
}