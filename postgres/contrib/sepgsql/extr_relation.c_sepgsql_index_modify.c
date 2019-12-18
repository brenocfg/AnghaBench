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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_index_indexrelid ; 
 int /*<<< orphan*/  Anum_pg_index_indrelid ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  IndexRelidIndexId ; 
 int /*<<< orphan*/  sepgsql_relation_setattr_extra (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sepgsql_index_modify(Oid indexOid)
{
	Relation	catalog = table_open(IndexRelationId, AccessShareLock);

	/* check db_table:{setattr} permission of the table being indexed */
	sepgsql_relation_setattr_extra(catalog,
								   IndexRelidIndexId,
								   indexOid,
								   Anum_pg_index_indrelid,
								   Anum_pg_index_indexrelid);
	table_close(catalog, AccessShareLock);
}