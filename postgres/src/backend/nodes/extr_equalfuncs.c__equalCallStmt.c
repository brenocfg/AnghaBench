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
typedef  int /*<<< orphan*/  CallStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funccall ; 
 int /*<<< orphan*/  funcexpr ; 

__attribute__((used)) static bool
_equalCallStmt(const CallStmt *a, const CallStmt *b)
{
	COMPARE_NODE_FIELD(funccall);
	COMPARE_NODE_FIELD(funcexpr);

	return true;
}