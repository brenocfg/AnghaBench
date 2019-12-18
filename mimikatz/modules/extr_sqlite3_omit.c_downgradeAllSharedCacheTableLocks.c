#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eLock; TYPE_1__* pBtree; struct TYPE_7__* pNext; } ;
struct TYPE_6__ {int btsFlags; TYPE_3__* pLock; TYPE_1__* pWriter; } ;
struct TYPE_5__ {TYPE_2__* pBt; } ;
typedef  TYPE_1__ Btree ;
typedef  TYPE_2__ BtShared ;
typedef  TYPE_3__ BtLock ;

/* Variables and functions */
 int BTS_EXCLUSIVE ; 
 int BTS_PENDING ; 
 scalar_t__ READ_LOCK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void downgradeAllSharedCacheTableLocks(Btree *p){
  BtShared *pBt = p->pBt;
  if( pBt->pWriter==p ){
    BtLock *pLock;
    pBt->pWriter = 0;
    pBt->btsFlags &= ~(BTS_EXCLUSIVE|BTS_PENDING);
    for(pLock=pBt->pLock; pLock; pLock=pLock->pNext){
      assert( pLock->eLock==READ_LOCK || pLock->pBtree==p );
      pLock->eLock = READ_LOCK;
    }
  }
}