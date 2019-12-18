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
typedef  int /*<<< orphan*/  AlterFunctionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  actions ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  objtype ; 

__attribute__((used)) static bool
_equalAlterFunctionStmt(const AlterFunctionStmt *a, const AlterFunctionStmt *b)
{
	COMPARE_SCALAR_FIELD(objtype);
	COMPARE_NODE_FIELD(func);
	COMPARE_NODE_FIELD(actions);

	return true;
}