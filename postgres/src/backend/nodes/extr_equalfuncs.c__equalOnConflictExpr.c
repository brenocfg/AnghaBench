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
typedef  int /*<<< orphan*/  OnConflictExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action ; 
 int /*<<< orphan*/  arbiterElems ; 
 int /*<<< orphan*/  arbiterWhere ; 
 int /*<<< orphan*/  constraint ; 
 int /*<<< orphan*/  exclRelIndex ; 
 int /*<<< orphan*/  exclRelTlist ; 
 int /*<<< orphan*/  onConflictSet ; 
 int /*<<< orphan*/  onConflictWhere ; 

__attribute__((used)) static bool
_equalOnConflictExpr(const OnConflictExpr *a, const OnConflictExpr *b)
{
	COMPARE_SCALAR_FIELD(action);
	COMPARE_NODE_FIELD(arbiterElems);
	COMPARE_NODE_FIELD(arbiterWhere);
	COMPARE_SCALAR_FIELD(constraint);
	COMPARE_NODE_FIELD(onConflictSet);
	COMPARE_NODE_FIELD(onConflictWhere);
	COMPARE_SCALAR_FIELD(exclRelIndex);
	COMPARE_NODE_FIELD(exclRelTlist);

	return true;
}