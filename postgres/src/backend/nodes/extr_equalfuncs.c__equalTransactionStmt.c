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
typedef  int /*<<< orphan*/  TransactionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  gid ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  savepoint_name ; 

__attribute__((used)) static bool
_equalTransactionStmt(const TransactionStmt *a, const TransactionStmt *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_NODE_FIELD(options);
	COMPARE_STRING_FIELD(savepoint_name);
	COMPARE_STRING_FIELD(gid);
	COMPARE_SCALAR_FIELD(chain);

	return true;
}