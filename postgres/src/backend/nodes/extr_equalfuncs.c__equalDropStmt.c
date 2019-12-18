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
typedef  int /*<<< orphan*/  DropStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  behavior ; 
 int /*<<< orphan*/  concurrent ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  objects ; 
 int /*<<< orphan*/  removeType ; 

__attribute__((used)) static bool
_equalDropStmt(const DropStmt *a, const DropStmt *b)
{
	COMPARE_NODE_FIELD(objects);
	COMPARE_SCALAR_FIELD(removeType);
	COMPARE_SCALAR_FIELD(behavior);
	COMPARE_SCALAR_FIELD(missing_ok);
	COMPARE_SCALAR_FIELD(concurrent);

	return true;
}