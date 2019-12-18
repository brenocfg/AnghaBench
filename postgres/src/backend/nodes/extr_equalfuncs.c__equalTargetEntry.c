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
typedef  int /*<<< orphan*/  TargetEntry ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr ; 
 int /*<<< orphan*/  resjunk ; 
 int /*<<< orphan*/  resname ; 
 int /*<<< orphan*/  resno ; 
 int /*<<< orphan*/  resorigcol ; 
 int /*<<< orphan*/  resorigtbl ; 
 int /*<<< orphan*/  ressortgroupref ; 

__attribute__((used)) static bool
_equalTargetEntry(const TargetEntry *a, const TargetEntry *b)
{
	COMPARE_NODE_FIELD(expr);
	COMPARE_SCALAR_FIELD(resno);
	COMPARE_STRING_FIELD(resname);
	COMPARE_SCALAR_FIELD(ressortgroupref);
	COMPARE_SCALAR_FIELD(resorigtbl);
	COMPARE_SCALAR_FIELD(resorigcol);
	COMPARE_SCALAR_FIELD(resjunk);

	return true;
}