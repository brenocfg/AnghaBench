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
typedef  int /*<<< orphan*/  CreateTableSpaceStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  owner ; 
 int /*<<< orphan*/  tablespacename ; 

__attribute__((used)) static bool
_equalCreateTableSpaceStmt(const CreateTableSpaceStmt *a, const CreateTableSpaceStmt *b)
{
	COMPARE_STRING_FIELD(tablespacename);
	COMPARE_NODE_FIELD(owner);
	COMPARE_STRING_FIELD(location);
	COMPARE_NODE_FIELD(options);

	return true;
}