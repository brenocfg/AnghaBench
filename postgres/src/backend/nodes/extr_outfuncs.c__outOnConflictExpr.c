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
typedef  int /*<<< orphan*/  OnConflictExpr ;

/* Variables and functions */
 int /*<<< orphan*/  OnConflictAction ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action ; 
 int /*<<< orphan*/  arbiterElems ; 
 int /*<<< orphan*/  arbiterWhere ; 
 int /*<<< orphan*/  constraint ; 
 int /*<<< orphan*/  exclRelIndex ; 
 int /*<<< orphan*/  exclRelTlist ; 
 int /*<<< orphan*/  onConflictSet ; 
 int /*<<< orphan*/  onConflictWhere ; 

__attribute__((used)) static void
_outOnConflictExpr(StringInfo str, const OnConflictExpr *node)
{
	WRITE_NODE_TYPE("ONCONFLICTEXPR");

	WRITE_ENUM_FIELD(action, OnConflictAction);
	WRITE_NODE_FIELD(arbiterElems);
	WRITE_NODE_FIELD(arbiterWhere);
	WRITE_OID_FIELD(constraint);
	WRITE_NODE_FIELD(onConflictSet);
	WRITE_NODE_FIELD(onConflictWhere);
	WRITE_INT_FIELD(exclRelIndex);
	WRITE_NODE_FIELD(exclRelTlist);
}