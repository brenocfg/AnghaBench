#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  create_toast_table (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  makeRangeVar (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_openrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
BootstrapToastTable(char *relName, Oid toastOid, Oid toastIndexOid)
{
	Relation	rel;

	rel = table_openrv(makeRangeVar(NULL, relName, -1), AccessExclusiveLock);

	if (rel->rd_rel->relkind != RELKIND_RELATION &&
		rel->rd_rel->relkind != RELKIND_MATVIEW)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not a table or materialized view",
						relName)));

	/* create_toast_table does all the work */
	if (!create_toast_table(rel, toastOid, toastIndexOid, (Datum) 0,
							AccessExclusiveLock, false))
		elog(ERROR, "\"%s\" does not require a toast table",
			 relName);

	table_close(rel, NoLock);
}