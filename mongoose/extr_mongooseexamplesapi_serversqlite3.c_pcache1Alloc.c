#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {int szSlot; scalar_t__ nFreeSlot; int bUnderPressure; scalar_t__ nReserve; int /*<<< orphan*/  mutex; TYPE_2__* pFree; TYPE_1__ grp; } ;
struct TYPE_5__ {struct TYPE_5__* pNext; } ;
typedef  int /*<<< orphan*/  PgHdr1 ;

/* Variables and functions */
 int /*<<< orphan*/  MEMTYPE_PCACHE ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_OVERFLOW ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_USED ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ pcache1 ; 
 void* sqlite3Malloc (int) ; 
 int sqlite3MallocSize (void*) ; 
 int /*<<< orphan*/  sqlite3MemdebugSetType (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3StatusAdd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3StatusSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_notheld (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *pcache1Alloc(int nByte){
  void *p = 0;
  assert( sqlite3_mutex_notheld(pcache1.grp.mutex) );
  sqlite3StatusSet(SQLITE_STATUS_PAGECACHE_SIZE, nByte);
  if( nByte<=pcache1.szSlot ){
    sqlite3_mutex_enter(pcache1.mutex);
    p = (PgHdr1 *)pcache1.pFree;
    if( p ){
      pcache1.pFree = pcache1.pFree->pNext;
      pcache1.nFreeSlot--;
      pcache1.bUnderPressure = pcache1.nFreeSlot<pcache1.nReserve;
      assert( pcache1.nFreeSlot>=0 );
      sqlite3StatusAdd(SQLITE_STATUS_PAGECACHE_USED, 1);
    }
    sqlite3_mutex_leave(pcache1.mutex);
  }
  if( p==0 ){
    /* Memory is not available in the SQLITE_CONFIG_PAGECACHE pool.  Get
    ** it from sqlite3Malloc instead.
    */
    p = sqlite3Malloc(nByte);
#ifndef SQLITE_DISABLE_PAGECACHE_OVERFLOW_STATS
    if( p ){
      int sz = sqlite3MallocSize(p);
      sqlite3_mutex_enter(pcache1.mutex);
      sqlite3StatusAdd(SQLITE_STATUS_PAGECACHE_OVERFLOW, sz);
      sqlite3_mutex_leave(pcache1.mutex);
    }
#endif
    sqlite3MemdebugSetType(p, MEMTYPE_PCACHE);
  }
  return p;
}