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
typedef  int /*<<< orphan*/  TableSampleClause ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  repeatable ; 
 int /*<<< orphan*/  tsmhandler ; 

__attribute__((used)) static bool
_equalTableSampleClause(const TableSampleClause *a, const TableSampleClause *b)
{
	COMPARE_SCALAR_FIELD(tsmhandler);
	COMPARE_NODE_FIELD(args);
	COMPARE_NODE_FIELD(repeatable);

	return true;
}