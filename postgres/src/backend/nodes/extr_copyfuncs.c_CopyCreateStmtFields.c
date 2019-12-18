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
 int /*<<< orphan*/  COPY_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_STRING_FIELD (int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static void
CopyCreateStmtFields(const CreateStmt *from, CreateStmt *newnode)
{
	COPY_NODE_FIELD(relation);
	COPY_NODE_FIELD(tableElts);
	COPY_NODE_FIELD(inhRelations);
	COPY_NODE_FIELD(partspec);
	COPY_NODE_FIELD(partbound);
	COPY_NODE_FIELD(ofTypename);
	COPY_NODE_FIELD(constraints);
	COPY_NODE_FIELD(options);
	COPY_SCALAR_FIELD(oncommit);
	COPY_STRING_FIELD(tablespacename);
	COPY_STRING_FIELD(accessMethod);
	COPY_SCALAR_FIELD(if_not_exists);
}