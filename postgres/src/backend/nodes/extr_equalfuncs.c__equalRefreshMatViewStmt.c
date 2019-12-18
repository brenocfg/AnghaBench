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
typedef  int /*<<< orphan*/  RefreshMatViewStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  concurrent ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  skipData ; 

__attribute__((used)) static bool
_equalRefreshMatViewStmt(const RefreshMatViewStmt *a, const RefreshMatViewStmt *b)
{
	COMPARE_SCALAR_FIELD(concurrent);
	COMPARE_SCALAR_FIELD(skipData);
	COMPARE_NODE_FIELD(relation);

	return true;
}