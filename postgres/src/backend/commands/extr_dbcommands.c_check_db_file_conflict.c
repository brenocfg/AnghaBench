#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_2__ {scalar_t__ oid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_tablespace ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 char* GetDatabasePath (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TableSpaceRelationId ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_db_file_conflict(Oid db_id)
{
	bool		result = false;
	Relation	rel;
	TableScanDesc scan;
	HeapTuple	tuple;

	rel = table_open(TableSpaceRelationId, AccessShareLock);
	scan = table_beginscan_catalog(rel, 0, NULL);
	while ((tuple = heap_getnext(scan, ForwardScanDirection)) != NULL)
	{
		Form_pg_tablespace spcform = (Form_pg_tablespace) GETSTRUCT(tuple);
		Oid			dsttablespace = spcform->oid;
		char	   *dstpath;
		struct stat st;

		/* Don't mess with the global tablespace */
		if (dsttablespace == GLOBALTABLESPACE_OID)
			continue;

		dstpath = GetDatabasePath(db_id, dsttablespace);

		if (lstat(dstpath, &st) == 0)
		{
			/* Found a conflicting file (or directory, whatever) */
			pfree(dstpath);
			result = true;
			break;
		}

		pfree(dstpath);
	}

	table_endscan(scan);
	table_close(rel, AccessShareLock);

	return result;
}