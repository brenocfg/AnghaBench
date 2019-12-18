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
typedef  int /*<<< orphan*/  CopyStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attlist ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  is_from ; 
 int /*<<< orphan*/  is_program ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  whereClause ; 

__attribute__((used)) static bool
_equalCopyStmt(const CopyStmt *a, const CopyStmt *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(query);
	COMPARE_NODE_FIELD(attlist);
	COMPARE_SCALAR_FIELD(is_from);
	COMPARE_SCALAR_FIELD(is_program);
	COMPARE_STRING_FIELD(filename);
	COMPARE_NODE_FIELD(options);
	COMPARE_NODE_FIELD(whereClause);

	return true;
}