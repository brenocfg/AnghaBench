#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ pDest; int iNext; TYPE_1__* pSrc; scalar_t__ isAttached; TYPE_3__* pSrcDb; TYPE_3__* pDestDb; } ;
typedef  TYPE_2__ sqlite3_backup ;
struct TYPE_16__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_14__ {int /*<<< orphan*/  nBackup; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ERROR ; 
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 int /*<<< orphan*/  SQLITE_NOMEM_BKPT ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ checkReadTransaction (TYPE_3__*,scalar_t__) ; 
 void* findBtree (TYPE_3__*,TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorWithMsg (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sqlite3MallocZero (int) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

sqlite3_backup *sqlite3_backup_init(
  sqlite3* pDestDb,                     /* Database to write to */
  const char *zDestDb,                  /* Name of database within pDestDb */
  sqlite3* pSrcDb,                      /* Database connection to read from */
  const char *zSrcDb                    /* Name of database within pSrcDb */
){
  sqlite3_backup *p;                    /* Value to return */

#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(pSrcDb)||!sqlite3SafetyCheckOk(pDestDb) ){
    (void)SQLITE_MISUSE_BKPT;
    return 0;
  }
#endif

  /* Lock the source database handle. The destination database
  ** handle is not locked in this routine, but it is locked in
  ** sqlite3_backup_step(). The user is required to ensure that no
  ** other thread accesses the destination handle for the duration
  ** of the backup operation.  Any attempt to use the destination
  ** database connection while a backup is in progress may cause
  ** a malfunction or a deadlock.
  */
  sqlite3_mutex_enter(pSrcDb->mutex);
  sqlite3_mutex_enter(pDestDb->mutex);

  if( pSrcDb==pDestDb ){
    sqlite3ErrorWithMsg(
        pDestDb, SQLITE_ERROR, "source and destination must be distinct"
    );
    p = 0;
  }else {
    /* Allocate space for a new sqlite3_backup object...
    ** EVIDENCE-OF: R-64852-21591 The sqlite3_backup object is created by a
    ** call to sqlite3_backup_init() and is destroyed by a call to
    ** sqlite3_backup_finish(). */
    p = (sqlite3_backup *)sqlite3MallocZero(sizeof(sqlite3_backup));
    if( !p ){
      sqlite3Error(pDestDb, SQLITE_NOMEM_BKPT);
    }
  }

  /* If the allocation succeeded, populate the new object. */
  if( p ){
    p->pSrc = findBtree(pDestDb, pSrcDb, zSrcDb);
    p->pDest = findBtree(pDestDb, pDestDb, zDestDb);
    p->pDestDb = pDestDb;
    p->pSrcDb = pSrcDb;
    p->iNext = 1;
    p->isAttached = 0;

    if( 0==p->pSrc || 0==p->pDest
     || checkReadTransaction(pDestDb, p->pDest)!=SQLITE_OK
     ){
      /* One (or both) of the named databases did not exist or an OOM
      ** error was hit. Or there is a transaction open on the destination
      ** database. The error has already been written into the pDestDb
      ** handle. All that is left to do here is free the sqlite3_backup
      ** structure.  */
      sqlite3_free(p);
      p = 0;
    }
  }
  if( p ){
    p->pSrc->nBackup++;
  }

  sqlite3_mutex_leave(pDestDb->mutex);
  sqlite3_mutex_leave(pSrcDb->mutex);
  return p;
}