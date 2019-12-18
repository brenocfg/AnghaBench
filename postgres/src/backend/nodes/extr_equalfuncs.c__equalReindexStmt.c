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
typedef  int /*<<< orphan*/  ReindexStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  concurrent ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  relation ; 

__attribute__((used)) static bool
_equalReindexStmt(const ReindexStmt *a, const ReindexStmt *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_NODE_FIELD(relation);
	COMPARE_STRING_FIELD(name);
	COMPARE_SCALAR_FIELD(options);
	COMPARE_SCALAR_FIELD(concurrent);

	return true;
}