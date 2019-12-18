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
typedef  int /*<<< orphan*/  ImportForeignSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ImportForeignSchemaType ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_type ; 
 int /*<<< orphan*/  local_schema ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  remote_schema ; 
 int /*<<< orphan*/  server_name ; 
 int /*<<< orphan*/  table_list ; 

__attribute__((used)) static void
_outImportForeignSchemaStmt(StringInfo str, const ImportForeignSchemaStmt *node)
{
	WRITE_NODE_TYPE("IMPORTFOREIGNSCHEMASTMT");

	WRITE_STRING_FIELD(server_name);
	WRITE_STRING_FIELD(remote_schema);
	WRITE_STRING_FIELD(local_schema);
	WRITE_ENUM_FIELD(list_type, ImportForeignSchemaType);
	WRITE_NODE_FIELD(table_list);
	WRITE_NODE_FIELD(options);
}