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
typedef  int /*<<< orphan*/  CreateStatsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defnames ; 
 int /*<<< orphan*/  exprs ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  relations ; 
 int /*<<< orphan*/  stat_types ; 
 int /*<<< orphan*/  stxcomment ; 

__attribute__((used)) static bool
_equalCreateStatsStmt(const CreateStatsStmt *a, const CreateStatsStmt *b)
{
	COMPARE_NODE_FIELD(defnames);
	COMPARE_NODE_FIELD(stat_types);
	COMPARE_NODE_FIELD(exprs);
	COMPARE_NODE_FIELD(relations);
	COMPARE_STRING_FIELD(stxcomment);
	COMPARE_SCALAR_FIELD(if_not_exists);

	return true;
}