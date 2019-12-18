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
typedef  int /*<<< orphan*/  ViewStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  replace ; 
 int /*<<< orphan*/  view ; 
 int /*<<< orphan*/  withCheckOption ; 

__attribute__((used)) static bool
_equalViewStmt(const ViewStmt *a, const ViewStmt *b)
{
	COMPARE_NODE_FIELD(view);
	COMPARE_NODE_FIELD(aliases);
	COMPARE_NODE_FIELD(query);
	COMPARE_SCALAR_FIELD(replace);
	COMPARE_NODE_FIELD(options);
	COMPARE_SCALAR_FIELD(withCheckOption);

	return true;
}