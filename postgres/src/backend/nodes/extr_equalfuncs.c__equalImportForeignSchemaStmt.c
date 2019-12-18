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
typedef  int /*<<< orphan*/  ImportForeignSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_type ; 
 int /*<<< orphan*/  local_schema ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  remote_schema ; 
 int /*<<< orphan*/  server_name ; 
 int /*<<< orphan*/  table_list ; 

__attribute__((used)) static bool
_equalImportForeignSchemaStmt(const ImportForeignSchemaStmt *a, const ImportForeignSchemaStmt *b)
{
	COMPARE_STRING_FIELD(server_name);
	COMPARE_STRING_FIELD(remote_schema);
	COMPARE_STRING_FIELD(local_schema);
	COMPARE_SCALAR_FIELD(list_type);
	COMPARE_NODE_FIELD(table_list);
	COMPARE_NODE_FIELD(options);

	return true;
}