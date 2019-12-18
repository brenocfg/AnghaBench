#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ts_id; } ;
typedef  TYPE_1__ xl_tblspc_drop_rec ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_12__ {char* tablespacename; int /*<<< orphan*/  missing_ok; } ;
struct TYPE_11__ {scalar_t__ oid; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_tablespace ;
typedef  TYPE_4__ DropTableSpaceStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  ACLCHECK_NO_PRIV ; 
 int /*<<< orphan*/  Anum_pg_tablespace_spcname ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int CHECKPOINT_FORCE ; 
 int CHECKPOINT_IMMEDIATE ; 
 int CHECKPOINT_WAIT ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DEFAULTTABLESPACE_OID ; 
 int /*<<< orphan*/  DeleteSharedComments (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteSharedSecurityLabel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  ForceSyncCommit () ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectDropHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_TABLESPACE ; 
 int /*<<< orphan*/  RM_TBLSPC_ID ; 
 int /*<<< orphan*/  RequestCheckpoint (int) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TableSpaceRelationId ; 
 int /*<<< orphan*/  TablespaceCreateLock ; 
 int /*<<< orphan*/  XLOG_TBLSPC_DROP ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  deleteSharedDependencyRecordsFor (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_tablespace_directories (scalar_t__,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_2__* heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_tablespace_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
DropTableSpace(DropTableSpaceStmt *stmt)
{
#ifdef HAVE_SYMLINK
	char	   *tablespacename = stmt->tablespacename;
	TableScanDesc scandesc;
	Relation	rel;
	HeapTuple	tuple;
	Form_pg_tablespace spcform;
	ScanKeyData entry[1];
	Oid			tablespaceoid;

	/*
	 * Find the target tuple
	 */
	rel = table_open(TableSpaceRelationId, RowExclusiveLock);

	ScanKeyInit(&entry[0],
				Anum_pg_tablespace_spcname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(tablespacename));
	scandesc = table_beginscan_catalog(rel, 1, entry);
	tuple = heap_getnext(scandesc, ForwardScanDirection);

	if (!HeapTupleIsValid(tuple))
	{
		if (!stmt->missing_ok)
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("tablespace \"%s\" does not exist",
							tablespacename)));
		}
		else
		{
			ereport(NOTICE,
					(errmsg("tablespace \"%s\" does not exist, skipping",
							tablespacename)));
			/* XXX I assume I need one or both of these next two calls */
			table_endscan(scandesc);
			table_close(rel, NoLock);
		}
		return;
	}

	spcform = (Form_pg_tablespace) GETSTRUCT(tuple);
	tablespaceoid = spcform->oid;

	/* Must be tablespace owner */
	if (!pg_tablespace_ownercheck(tablespaceoid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_TABLESPACE,
					   tablespacename);

	/* Disallow drop of the standard tablespaces, even by superuser */
	if (tablespaceoid == GLOBALTABLESPACE_OID ||
		tablespaceoid == DEFAULTTABLESPACE_OID)
		aclcheck_error(ACLCHECK_NO_PRIV, OBJECT_TABLESPACE,
					   tablespacename);

	/* DROP hook for the tablespace being removed */
	InvokeObjectDropHook(TableSpaceRelationId, tablespaceoid, 0);

	/*
	 * Remove the pg_tablespace tuple (this will roll back if we fail below)
	 */
	CatalogTupleDelete(rel, &tuple->t_self);

	table_endscan(scandesc);

	/*
	 * Remove any comments or security labels on this tablespace.
	 */
	DeleteSharedComments(tablespaceoid, TableSpaceRelationId);
	DeleteSharedSecurityLabel(tablespaceoid, TableSpaceRelationId);

	/*
	 * Remove dependency on owner.
	 */
	deleteSharedDependencyRecordsFor(TableSpaceRelationId, tablespaceoid, 0);

	/*
	 * Acquire TablespaceCreateLock to ensure that no TablespaceCreateDbspace
	 * is running concurrently.
	 */
	LWLockAcquire(TablespaceCreateLock, LW_EXCLUSIVE);

	/*
	 * Try to remove the physical infrastructure.
	 */
	if (!destroy_tablespace_directories(tablespaceoid, false))
	{
		/*
		 * Not all files deleted?  However, there can be lingering empty files
		 * in the directories, left behind by for example DROP TABLE, that
		 * have been scheduled for deletion at next checkpoint (see comments
		 * in mdunlink() for details).  We could just delete them immediately,
		 * but we can't tell them apart from important data files that we
		 * mustn't delete.  So instead, we force a checkpoint which will clean
		 * out any lingering files, and try again.
		 *
		 * XXX On Windows, an unlinked file persists in the directory listing
		 * until no process retains an open handle for the file.  The DDL
		 * commands that schedule files for unlink send invalidation messages
		 * directing other PostgreSQL processes to close the files.  DROP
		 * TABLESPACE should not give up on the tablespace becoming empty
		 * until all relevant invalidation processing is complete.
		 */
		RequestCheckpoint(CHECKPOINT_IMMEDIATE | CHECKPOINT_FORCE | CHECKPOINT_WAIT);
		if (!destroy_tablespace_directories(tablespaceoid, false))
		{
			/* Still not empty, the files must be important then */
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("tablespace \"%s\" is not empty",
							tablespacename)));
		}
	}

	/* Record the filesystem change in XLOG */
	{
		xl_tblspc_drop_rec xlrec;

		xlrec.ts_id = tablespaceoid;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, sizeof(xl_tblspc_drop_rec));

		(void) XLogInsert(RM_TBLSPC_ID, XLOG_TBLSPC_DROP);
	}

	/*
	 * Note: because we checked that the tablespace was empty, there should be
	 * no need to worry about flushing shared buffers or free space map
	 * entries for relations in the tablespace.
	 */

	/*
	 * Force synchronous commit, to minimize the window between removing the
	 * files on-disk and marking the transaction committed.  It's not great
	 * that there is any window at all, but definitely we don't want to make
	 * it larger than necessary.
	 */
	ForceSyncCommit();

	/*
	 * Allow TablespaceCreateDbspace again.
	 */
	LWLockRelease(TablespaceCreateLock);

	/* We keep the lock on pg_tablespace until commit */
	table_close(rel, NoLock);
#else							/* !HAVE_SYMLINK */
	ereport(ERROR,
			(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
			 errmsg("tablespaces are not supported on this platform")));
#endif							/* HAVE_SYMLINK */
}