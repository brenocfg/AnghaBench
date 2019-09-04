#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int nDb; int mallocFailed; TYPE_2__* aDb; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_11__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  checkSchema; TYPE_3__* db; } ;
struct TYPE_9__ {TYPE_1__* pSchema; int /*<<< orphan*/ * pBt; } ;
struct TYPE_8__ {int schema_cookie; } ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_SCHEMA_VERSION ; 
 int SQLITE_IOERR_NOMEM ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_SCHEMA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int sqlite3BtreeBeginTrans (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeCommit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeGetMeta (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeIsInReadTrans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ResetOneSchema (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3SchemaMutexHeld (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void schemaIsValid(Parse *pParse){
  sqlite3 *db = pParse->db;
  int iDb;
  int rc;
  int cookie;

  assert( pParse->checkSchema );
  assert( sqlite3_mutex_held(db->mutex) );
  for(iDb=0; iDb<db->nDb; iDb++){
    int openedTransaction = 0;         /* True if a transaction is opened */
    Btree *pBt = db->aDb[iDb].pBt;     /* Btree database to read cookie from */
    if( pBt==0 ) continue;

    /* If there is not already a read-only (or read-write) transaction opened
    ** on the b-tree database, open one now. If a transaction is opened, it 
    ** will be closed immediately after reading the meta-value. */
    if( !sqlite3BtreeIsInReadTrans(pBt) ){
      rc = sqlite3BtreeBeginTrans(pBt, 0);
      if( rc==SQLITE_NOMEM || rc==SQLITE_IOERR_NOMEM ){
        db->mallocFailed = 1;
      }
      if( rc!=SQLITE_OK ) return;
      openedTransaction = 1;
    }

    /* Read the schema cookie from the database. If it does not match the 
    ** value stored as part of the in-memory schema representation,
    ** set Parse.rc to SQLITE_SCHEMA. */
    sqlite3BtreeGetMeta(pBt, BTREE_SCHEMA_VERSION, (u32 *)&cookie);
    assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
    if( cookie!=db->aDb[iDb].pSchema->schema_cookie ){
      sqlite3ResetOneSchema(db, iDb);
      pParse->rc = SQLITE_SCHEMA;
    }

    /* Close the transaction, if one was opened. */
    if( openedTransaction ){
      sqlite3BtreeCommit(pBt);
    }
  }
}