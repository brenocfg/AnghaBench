#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {int nDb; int (* xCommitCallback ) (int /*<<< orphan*/ ) ;TYPE_1__* aDb; int /*<<< orphan*/ * pVfs; int /*<<< orphan*/  pCommitArg; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  iRandom ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_8__ {scalar_t__ safety_level; int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  Pager ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 scalar_t__ PAGER_SYNCHRONOUS_OFF ; 
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_BUSY ; 
 int SQLITE_CONSTRAINT_COMMITHOOK ; 
 int /*<<< orphan*/  SQLITE_FULL ; 
 int SQLITE_IOCAP_SEQUENTIAL ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_EXCLUSIVE ; 
 int SQLITE_OPEN_MASTER_JOURNAL ; 
 int SQLITE_OPEN_READWRITE ; 
 int /*<<< orphan*/  SQLITE_SYNC_NORMAL ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disable_simulated_io_errors () ; 
 int /*<<< orphan*/  enable_simulated_io_errors () ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int sqlite3BtreeCommitPhaseOne (int /*<<< orphan*/ *,char*) ; 
 int sqlite3BtreeCommitPhaseTwo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (int /*<<< orphan*/ *) ; 
 char const* sqlite3BtreeGetFilename (int /*<<< orphan*/ *) ; 
 char* sqlite3BtreeGetJournalname (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3BtreeIsInTrans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3BtreePager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3FileSuffix3 (char const*,char*) ; 
 char* sqlite3MPrintf (TYPE_2__*,char*,char const*) ; 
 int sqlite3OsAccess (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3OsCloseFree (int /*<<< orphan*/ *) ; 
 int sqlite3OsDelete (int /*<<< orphan*/ *,char*,int) ; 
 int sqlite3OsDeviceCharacteristics (int /*<<< orphan*/ *) ; 
 int sqlite3OsOpenMalloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int sqlite3OsSync (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3PagerExclusiveLock (int /*<<< orphan*/ *) ; 
 size_t sqlite3PagerGetJournalMode (int /*<<< orphan*/ *) ; 
 int sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3VtabCommit (TYPE_2__*) ; 
 int sqlite3VtabSync (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,int*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdbeCommit(sqlite3 *db, Vdbe *p){
  int i;
  int nTrans = 0;  /* Number of databases with an active write-transaction
                   ** that are candidates for a two-phase commit using a
                   ** master-journal */
  int rc = SQLITE_OK;
  int needXcommit = 0;

#ifdef SQLITE_OMIT_VIRTUALTABLE
  /* With this option, sqlite3VtabSync() is defined to be simply
  ** SQLITE_OK so p is not used.
  */
  UNUSED_PARAMETER(p);
#endif

  /* Before doing anything else, call the xSync() callback for any
  ** virtual module tables written in this transaction. This has to
  ** be done before determining whether a master journal file is
  ** required, as an xSync() callback may add an attached database
  ** to the transaction.
  */
  rc = sqlite3VtabSync(db, p);

  /* This loop determines (a) if the commit hook should be invoked and
  ** (b) how many database files have open write transactions, not
  ** including the temp database. (b) is important because if more than
  ** one database file has an open write transaction, a master journal
  ** file is required for an atomic commit.
  */
  for(i=0; rc==SQLITE_OK && i<db->nDb; i++){
    Btree *pBt = db->aDb[i].pBt;
    if( sqlite3BtreeIsInTrans(pBt) ){
      /* Whether or not a database might need a master journal depends upon
      ** its journal mode (among other things).  This matrix determines which
      ** journal modes use a master journal and which do not */
      static const u8 aMJNeeded[] = {
        /* DELETE   */  1,
        /* PERSIST   */ 1,
        /* OFF       */ 0,
        /* TRUNCATE  */ 1,
        /* MEMORY    */ 0,
        /* WAL       */ 0
      };
      Pager *pPager;   /* Pager associated with pBt */
      needXcommit = 1;
      sqlite3BtreeEnter(pBt);
      pPager = sqlite3BtreePager(pBt);
      if( db->aDb[i].safety_level!=PAGER_SYNCHRONOUS_OFF
       && aMJNeeded[sqlite3PagerGetJournalMode(pPager)]
      ){
        assert( i!=1 );
        nTrans++;
      }
      rc = sqlite3PagerExclusiveLock(pPager);
      sqlite3BtreeLeave(pBt);
    }
  }
  if( rc!=SQLITE_OK ){
    return rc;
  }

  /* If there are any write-transactions at all, invoke the commit hook */
  if( needXcommit && db->xCommitCallback ){
    rc = db->xCommitCallback(db->pCommitArg);
    if( rc ){
      return SQLITE_CONSTRAINT_COMMITHOOK;
    }
  }

  /* The simple case - no more than one database file (not counting the
  ** TEMP database) has a transaction active.   There is no need for the
  ** master-journal.
  **
  ** If the return value of sqlite3BtreeGetFilename() is a zero length
  ** string, it means the main database is :memory: or a temp file.  In
  ** that case we do not support atomic multi-file commits, so use the
  ** simple case then too.
  */
  if( 0==sqlite3Strlen30(sqlite3BtreeGetFilename(db->aDb[0].pBt))
   || nTrans<=1
  ){
    for(i=0; rc==SQLITE_OK && i<db->nDb; i++){
      Btree *pBt = db->aDb[i].pBt;
      if( pBt ){
        rc = sqlite3BtreeCommitPhaseOne(pBt, 0);
      }
    }

    /* Do the commit only if all databases successfully complete phase 1.
    ** If one of the BtreeCommitPhaseOne() calls fails, this indicates an
    ** IO error while deleting or truncating a journal file. It is unlikely,
    ** but could happen. In this case abandon processing and return the error.
    */
    for(i=0; rc==SQLITE_OK && i<db->nDb; i++){
      Btree *pBt = db->aDb[i].pBt;
      if( pBt ){
        rc = sqlite3BtreeCommitPhaseTwo(pBt, 0);
      }
    }
    if( rc==SQLITE_OK ){
      sqlite3VtabCommit(db);
    }
  }

  /* The complex case - There is a multi-file write-transaction active.
  ** This requires a master journal file to ensure the transaction is
  ** committed atomically.
  */
#ifndef SQLITE_OMIT_DISKIO
  else{
    sqlite3_vfs *pVfs = db->pVfs;
    char *zMaster = 0;   /* File-name for the master journal */
    char const *zMainFile = sqlite3BtreeGetFilename(db->aDb[0].pBt);
    sqlite3_file *pMaster = 0;
    i64 offset = 0;
    int res;
    int retryCount = 0;
    int nMainFile;

    /* Select a master journal file name */
    nMainFile = sqlite3Strlen30(zMainFile);
    zMaster = sqlite3MPrintf(db, "%s-mjXXXXXX9XXz", zMainFile);
    if( zMaster==0 ) return SQLITE_NOMEM_BKPT;
    do {
      u32 iRandom;
      if( retryCount ){
        if( retryCount>100 ){
          sqlite3_log(SQLITE_FULL, "MJ delete: %s", zMaster);
          sqlite3OsDelete(pVfs, zMaster, 0);
          break;
        }else if( retryCount==1 ){
          sqlite3_log(SQLITE_FULL, "MJ collide: %s", zMaster);
        }
      }
      retryCount++;
      sqlite3_randomness(sizeof(iRandom), &iRandom);
      sqlite3_snprintf(13, &zMaster[nMainFile], "-mj%06X9%02X",
                               (iRandom>>8)&0xffffff, iRandom&0xff);
      /* The antipenultimate character of the master journal name must
      ** be "9" to avoid name collisions when using 8+3 filenames. */
      assert( zMaster[sqlite3Strlen30(zMaster)-3]=='9' );
      sqlite3FileSuffix3(zMainFile, zMaster);
      rc = sqlite3OsAccess(pVfs, zMaster, SQLITE_ACCESS_EXISTS, &res);
    }while( rc==SQLITE_OK && res );
    if( rc==SQLITE_OK ){
      /* Open the master journal. */
      rc = sqlite3OsOpenMalloc(pVfs, zMaster, &pMaster,
          SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|
          SQLITE_OPEN_EXCLUSIVE|SQLITE_OPEN_MASTER_JOURNAL, 0
      );
    }
    if( rc!=SQLITE_OK ){
      sqlite3DbFree(db, zMaster);
      return rc;
    }

    /* Write the name of each database file in the transaction into the new
    ** master journal file. If an error occurs at this point close
    ** and delete the master journal file. All the individual journal files
    ** still have 'null' as the master journal pointer, so they will roll
    ** back independently if a failure occurs.
    */
    for(i=0; i<db->nDb; i++){
      Btree *pBt = db->aDb[i].pBt;
      if( sqlite3BtreeIsInTrans(pBt) ){
        char const *zFile = sqlite3BtreeGetJournalname(pBt);
        if( zFile==0 ){
          continue;  /* Ignore TEMP and :memory: databases */
        }
        assert( zFile[0]!=0 );
        rc = sqlite3OsWrite(pMaster, zFile, sqlite3Strlen30(zFile)+1, offset);
        offset += sqlite3Strlen30(zFile)+1;
        if( rc!=SQLITE_OK ){
          sqlite3OsCloseFree(pMaster);
          sqlite3OsDelete(pVfs, zMaster, 0);
          sqlite3DbFree(db, zMaster);
          return rc;
        }
      }
    }

    /* Sync the master journal file. If the IOCAP_SEQUENTIAL device
    ** flag is set this is not required.
    */
    if( 0==(sqlite3OsDeviceCharacteristics(pMaster)&SQLITE_IOCAP_SEQUENTIAL)
     && SQLITE_OK!=(rc = sqlite3OsSync(pMaster, SQLITE_SYNC_NORMAL))
    ){
      sqlite3OsCloseFree(pMaster);
      sqlite3OsDelete(pVfs, zMaster, 0);
      sqlite3DbFree(db, zMaster);
      return rc;
    }

    /* Sync all the db files involved in the transaction. The same call
    ** sets the master journal pointer in each individual journal. If
    ** an error occurs here, do not delete the master journal file.
    **
    ** If the error occurs during the first call to
    ** sqlite3BtreeCommitPhaseOne(), then there is a chance that the
    ** master journal file will be orphaned. But we cannot delete it,
    ** in case the master journal file name was written into the journal
    ** file before the failure occurred.
    */
    for(i=0; rc==SQLITE_OK && i<db->nDb; i++){
      Btree *pBt = db->aDb[i].pBt;
      if( pBt ){
        rc = sqlite3BtreeCommitPhaseOne(pBt, zMaster);
      }
    }
    sqlite3OsCloseFree(pMaster);
    assert( rc!=SQLITE_BUSY );
    if( rc!=SQLITE_OK ){
      sqlite3DbFree(db, zMaster);
      return rc;
    }

    /* Delete the master journal file. This commits the transaction. After
    ** doing this the directory is synced again before any individual
    ** transaction files are deleted.
    */
    rc = sqlite3OsDelete(pVfs, zMaster, 1);
    sqlite3DbFree(db, zMaster);
    zMaster = 0;
    if( rc ){
      return rc;
    }

    /* All files and directories have already been synced, so the following
    ** calls to sqlite3BtreeCommitPhaseTwo() are only closing files and
    ** deleting or truncating journals. If something goes wrong while
    ** this is happening we don't really care. The integrity of the
    ** transaction is already guaranteed, but some stray 'cold' journals
    ** may be lying around. Returning an error code won't help matters.
    */
    disable_simulated_io_errors();
    sqlite3BeginBenignMalloc();
    for(i=0; i<db->nDb; i++){
      Btree *pBt = db->aDb[i].pBt;
      if( pBt ){
        sqlite3BtreeCommitPhaseTwo(pBt, 1);
      }
    }
    sqlite3EndBenignMalloc();
    enable_simulated_io_errors();

    sqlite3VtabCommit(db);
  }
#endif

  return rc;
}