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
typedef  int /*<<< orphan*/  CreateStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accessMethod ; 
 int /*<<< orphan*/  constraints ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  inhRelations ; 
 int /*<<< orphan*/  ofTypename ; 
 int /*<<< orphan*/  oncommit ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  partbound ; 
 int /*<<< orphan*/  partspec ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  tableElts ; 
 int /*<<< orphan*/  tablespacename ; 

__attribute__((used)) static bool
_equalCreateStmt(const CreateStmt *a, const CreateStmt *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(tableElts);
	COMPARE_NODE_FIELD(inhRelations);
	COMPARE_NODE_FIELD(partbound);
	COMPARE_NODE_FIELD(partspec);
	COMPARE_NODE_FIELD(ofTypename);
	COMPARE_NODE_FIELD(constraints);
	COMPARE_NODE_FIELD(options);
	COMPARE_SCALAR_FIELD(oncommit);
	COMPARE_STRING_FIELD(tablespacename);
	COMPARE_STRING_FIELD(accessMethod);
	COMPARE_SCALAR_FIELD(if_not_exists);

	return true;
}