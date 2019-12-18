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
typedef  int /*<<< orphan*/  AlterEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newVal ; 
 int /*<<< orphan*/  newValIsAfter ; 
 int /*<<< orphan*/  newValNeighbor ; 
 int /*<<< orphan*/  oldVal ; 
 int /*<<< orphan*/  skipIfNewValExists ; 
 int /*<<< orphan*/  typeName ; 

__attribute__((used)) static bool
_equalAlterEnumStmt(const AlterEnumStmt *a, const AlterEnumStmt *b)
{
	COMPARE_NODE_FIELD(typeName);
	COMPARE_STRING_FIELD(oldVal);
	COMPARE_STRING_FIELD(newVal);
	COMPARE_STRING_FIELD(newValNeighbor);
	COMPARE_SCALAR_FIELD(newValIsAfter);
	COMPARE_SCALAR_FIELD(skipIfNewValExists);

	return true;
}