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
typedef  int /*<<< orphan*/  IntoClause ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accessMethod ; 
 int /*<<< orphan*/  colNames ; 
 int /*<<< orphan*/  onCommit ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  rel ; 
 int /*<<< orphan*/  skipData ; 
 int /*<<< orphan*/  tableSpaceName ; 
 int /*<<< orphan*/  viewQuery ; 

__attribute__((used)) static bool
_equalIntoClause(const IntoClause *a, const IntoClause *b)
{
	COMPARE_NODE_FIELD(rel);
	COMPARE_NODE_FIELD(colNames);
	COMPARE_STRING_FIELD(accessMethod);
	COMPARE_NODE_FIELD(options);
	COMPARE_SCALAR_FIELD(onCommit);
	COMPARE_STRING_FIELD(tableSpaceName);
	COMPARE_NODE_FIELD(viewQuery);
	COMPARE_SCALAR_FIELD(skipData);

	return true;
}