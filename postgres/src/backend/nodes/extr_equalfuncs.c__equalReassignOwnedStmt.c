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
typedef  int /*<<< orphan*/  ReassignOwnedStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newrole ; 
 int /*<<< orphan*/  roles ; 

__attribute__((used)) static bool
_equalReassignOwnedStmt(const ReassignOwnedStmt *a, const ReassignOwnedStmt *b)
{
	COMPARE_NODE_FIELD(roles);
	COMPARE_NODE_FIELD(newrole);

	return true;
}