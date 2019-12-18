#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tablespace_id; scalar_t__ db_id; } ;
typedef  TYPE_1__ xl_dbase_drop_rec ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_4__ {scalar_t__ oid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_tablespace ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 char* GetDatabasePath (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RM_DBASE_ID ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TableSpaceRelationId ; 
 int /*<<< orphan*/  WARNING ; 
 int XLOG_DBASE_DROP ; 
 int XLR_SPECIAL_REL_UPDATE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_dbtablespaces(Oid db_id)
{
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

		if (lstat(dstpath, &st) < 0 || !S_ISDIR(st.st_mode))
		{
			/* Assume we can ignore it */
			pfree(dstpath);
			continue;
		}

		if (!rmtree(dstpath, true))
			ereport(WARNING,
					(errmsg("some useless files may be left behind in old database directory \"%s\"",
							dstpath)));

		/* Record the filesystem change in XLOG */
		{
			xl_dbase_drop_rec xlrec;

			xlrec.db_id = db_id;
			xlrec.tablespace_id = dsttablespace;

			XLogBeginInsert();
			XLogRegisterData((char *) &xlrec, sizeof(xl_dbase_drop_rec));

			(void) XLogInsert(RM_DBASE_ID,
							  XLOG_DBASE_DROP | XLR_SPECIAL_REL_UPDATE);
		}

		pfree(dstpath);
	}

	table_endscan(scan);
	table_close(rel, AccessShareLock);
}