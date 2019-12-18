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
typedef  int /*<<< orphan*/  CreateSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authrole ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  schemaElts ; 
 int /*<<< orphan*/  schemaname ; 

__attribute__((used)) static bool
_equalCreateSchemaStmt(const CreateSchemaStmt *a, const CreateSchemaStmt *b)
{
	COMPARE_STRING_FIELD(schemaname);
	COMPARE_NODE_FIELD(authrole);
	COMPARE_NODE_FIELD(schemaElts);
	COMPARE_SCALAR_FIELD(if_not_exists);

	return true;
}