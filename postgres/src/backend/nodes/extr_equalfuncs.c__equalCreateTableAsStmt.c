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
typedef  int /*<<< orphan*/  CreateTableAsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  into ; 
 int /*<<< orphan*/  is_select_into ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  relkind ; 

__attribute__((used)) static bool
_equalCreateTableAsStmt(const CreateTableAsStmt *a, const CreateTableAsStmt *b)
{
	COMPARE_NODE_FIELD(query);
	COMPARE_NODE_FIELD(into);
	COMPARE_SCALAR_FIELD(relkind);
	COMPARE_SCALAR_FIELD(is_select_into);
	COMPARE_SCALAR_FIELD(if_not_exists);

	return true;
}