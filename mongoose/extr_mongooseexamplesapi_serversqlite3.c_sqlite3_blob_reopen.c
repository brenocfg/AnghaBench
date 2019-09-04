#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_blob ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_8__ {scalar_t__ pStmt; TYPE_1__* db; } ;
typedef  TYPE_2__ Incrblob ;

/* Variables and functions */
 int SQLITE_ABORT ; 
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_SCHEMA ; 
 int /*<<< orphan*/  assert (int) ; 
 int blobSeekToRow (TYPE_2__*,int /*<<< orphan*/ ,char**) ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_1__*,int,char*,char*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_blob_reopen(sqlite3_blob *pBlob, sqlite3_int64 iRow){
  int rc;
  Incrblob *p = (Incrblob *)pBlob;
  sqlite3 *db;

  if( p==0 ) return SQLITE_MISUSE_BKPT;
  db = p->db;
  sqlite3_mutex_enter(db->mutex);

  if( p->pStmt==0 ){
    /* If there is no statement handle, then the blob-handle has
    ** already been invalidated. Return SQLITE_ABORT in this case.
    */
    rc = SQLITE_ABORT;
  }else{
    char *zErr;
    rc = blobSeekToRow(p, iRow, &zErr);
    if( rc!=SQLITE_OK ){
      sqlite3Error(db, rc, (zErr ? "%s" : 0), zErr);
      sqlite3DbFree(db, zErr);
    }
    assert( rc!=SQLITE_SCHEMA );
  }

  rc = sqlite3ApiExit(db, rc);
  assert( rc==SQLITE_OK || p->pStmt==0 );
  sqlite3_mutex_leave(db->mutex);
  return rc;
}