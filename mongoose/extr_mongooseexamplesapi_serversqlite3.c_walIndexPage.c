#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  volatile u32 ;
struct TYPE_3__ {int nWiData; scalar_t__ exclusiveMode; int /*<<< orphan*/  volatile** apWiData; int /*<<< orphan*/  readOnly; int /*<<< orphan*/  writeLock; int /*<<< orphan*/  pDbFd; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_READONLY ; 
 int /*<<< orphan*/  WALINDEX_PGSZ ; 
 scalar_t__ WAL_HEAPMEMORY_MODE ; 
 int /*<<< orphan*/  WAL_SHM_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3MallocZero (int /*<<< orphan*/ ) ; 
 int sqlite3OsShmMap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void volatile**) ; 
 scalar_t__ sqlite3_realloc (void*,int) ; 

__attribute__((used)) static int walIndexPage(Wal *pWal, int iPage, volatile u32 **ppPage){
  int rc = SQLITE_OK;

  /* Enlarge the pWal->apWiData[] array if required */
  if( pWal->nWiData<=iPage ){
    int nByte = sizeof(u32*)*(iPage+1);
    volatile u32 **apNew;
    apNew = (volatile u32 **)sqlite3_realloc((void *)pWal->apWiData, nByte);
    if( !apNew ){
      *ppPage = 0;
      return SQLITE_NOMEM;
    }
    memset((void*)&apNew[pWal->nWiData], 0,
           sizeof(u32*)*(iPage+1-pWal->nWiData));
    pWal->apWiData = apNew;
    pWal->nWiData = iPage+1;
  }

  /* Request a pointer to the required page from the VFS */
  if( pWal->apWiData[iPage]==0 ){
    if( pWal->exclusiveMode==WAL_HEAPMEMORY_MODE ){
      pWal->apWiData[iPage] = (u32 volatile *)sqlite3MallocZero(WALINDEX_PGSZ);
      if( !pWal->apWiData[iPage] ) rc = SQLITE_NOMEM;
    }else{
      rc = sqlite3OsShmMap(pWal->pDbFd, iPage, WALINDEX_PGSZ, 
          pWal->writeLock, (void volatile **)&pWal->apWiData[iPage]
      );
      if( rc==SQLITE_READONLY ){
        pWal->readOnly |= WAL_SHM_RDONLY;
        rc = SQLITE_OK;
      }
    }
  }

  *ppPage = pWal->apWiData[iPage];
  assert( iPage==0 || *ppPage || rc!=SQLITE_OK );
  return rc;
}