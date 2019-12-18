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
typedef  int /*<<< orphan*/  CreateEnumStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeName ; 
 int /*<<< orphan*/  vals ; 

__attribute__((used)) static bool
_equalCreateEnumStmt(const CreateEnumStmt *a, const CreateEnumStmt *b)
{
	COMPARE_NODE_FIELD(typeName);
	COMPARE_NODE_FIELD(vals);

	return true;
}