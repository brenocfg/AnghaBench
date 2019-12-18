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
typedef  int /*<<< orphan*/  RenameStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  behavior ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  newname ; 
 int /*<<< orphan*/  object ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  relationType ; 
 int /*<<< orphan*/  renameType ; 
 int /*<<< orphan*/  subname ; 

__attribute__((used)) static bool
_equalRenameStmt(const RenameStmt *a, const RenameStmt *b)
{
	COMPARE_SCALAR_FIELD(renameType);
	COMPARE_SCALAR_FIELD(relationType);
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(object);
	COMPARE_STRING_FIELD(subname);
	COMPARE_STRING_FIELD(newname);
	COMPARE_SCALAR_FIELD(behavior);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}