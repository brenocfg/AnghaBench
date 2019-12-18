#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nTransaction; scalar_t__ inTransaction; scalar_t__ bDoTruncate; } ;
struct TYPE_11__ {scalar_t__ inTrans; TYPE_1__* db; TYPE_3__* pBt; } ;
struct TYPE_10__ {int activeVdbeCnt; } ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 scalar_t__ TRANS_NONE ; 
 scalar_t__ TRANS_READ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btreeIntegrity (TYPE_2__*) ; 
 int /*<<< orphan*/  clearAllSharedCacheTableLocks (TYPE_2__*) ; 
 int /*<<< orphan*/  downgradeAllSharedCacheTableLocks (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeHoldsMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  unlockBtreeIfUnused (TYPE_3__*) ; 

__attribute__((used)) static void btreeEndTransaction(Btree *p){
  BtShared *pBt = p->pBt;
  assert( sqlite3BtreeHoldsMutex(p) );

#ifndef SQLITE_OMIT_AUTOVACUUM
  pBt->bDoTruncate = 0;
#endif
  if( p->inTrans>TRANS_NONE && p->db->activeVdbeCnt>1 ){
    /* If there are other active statements that belong to this database
    ** handle, downgrade to a read-only transaction. The other statements
    ** may still be reading from the database.  */
    downgradeAllSharedCacheTableLocks(p);
    p->inTrans = TRANS_READ;
  }else{
    /* If the handle had any kind of transaction open, decrement the 
    ** transaction count of the shared btree. If the transaction count 
    ** reaches 0, set the shared state to TRANS_NONE. The unlockBtreeIfUnused()
    ** call below will unlock the pager.  */
    if( p->inTrans!=TRANS_NONE ){
      clearAllSharedCacheTableLocks(p);
      pBt->nTransaction--;
      if( 0==pBt->nTransaction ){
        pBt->inTransaction = TRANS_NONE;
      }
    }

    /* Set the current transaction state to TRANS_NONE and unlock the 
    ** pager if this call closed the only read or write transaction.  */
    p->inTrans = TRANS_NONE;
    unlockBtreeIfUnused(pBt);
  }

  btreeIntegrity(p);
}