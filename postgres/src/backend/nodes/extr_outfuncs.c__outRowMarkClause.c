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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  RowMarkClause ;

/* Variables and functions */
 int /*<<< orphan*/  LockClauseStrength ; 
 int /*<<< orphan*/  LockWaitPolicy ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushedDown ; 
 int /*<<< orphan*/  rti ; 
 int /*<<< orphan*/  strength ; 
 int /*<<< orphan*/  waitPolicy ; 

__attribute__((used)) static void
_outRowMarkClause(StringInfo str, const RowMarkClause *node)
{
	WRITE_NODE_TYPE("ROWMARKCLAUSE");

	WRITE_UINT_FIELD(rti);
	WRITE_ENUM_FIELD(strength, LockClauseStrength);
	WRITE_ENUM_FIELD(waitPolicy, LockWaitPolicy);
	WRITE_BOOL_FIELD(pushedDown);
}