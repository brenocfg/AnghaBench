#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_8__ {int isAnchor; struct TYPE_8__* pLruNext; struct TYPE_8__* pLruPrev; } ;
struct TYPE_9__ {int mxPinned; int nMinPage; int nMaxPage; TYPE_1__ lru; } ;
struct TYPE_11__ {int separateCache; TYPE_2__ grp; } ;
struct TYPE_10__ {int szPage; int szExtra; int bPurgeable; int nMin; scalar_t__ nHash; scalar_t__ szAlloc; TYPE_2__* pGroup; } ;
typedef  int /*<<< orphan*/  PgHdr1 ;
typedef  TYPE_2__ PGroup ;
typedef  TYPE_3__ PCache1 ;

/* Variables and functions */
 scalar_t__ ROUND8 (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__ pcache1 ; 
 int /*<<< orphan*/  pcache1Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1ResizeHash (TYPE_3__*) ; 
 scalar_t__ sqlite3MallocZero (int) ; 

__attribute__((used)) static sqlite3_pcache *pcache1Create(int szPage, int szExtra, int bPurgeable){
  PCache1 *pCache;      /* The newly created page cache */
  PGroup *pGroup;       /* The group the new page cache will belong to */
  int sz;               /* Bytes of memory required to allocate the new cache */

  assert( (szPage & (szPage-1))==0 && szPage>=512 && szPage<=65536 );
  assert( szExtra < 300 );

  sz = sizeof(PCache1) + sizeof(PGroup)*pcache1.separateCache;
  pCache = (PCache1 *)sqlite3MallocZero(sz);
  if( pCache ){
    if( pcache1.separateCache ){
      pGroup = (PGroup*)&pCache[1];
      pGroup->mxPinned = 10;
    }else{
      pGroup = &pcache1.grp;
    }
    if( pGroup->lru.isAnchor==0 ){
      pGroup->lru.isAnchor = 1;
      pGroup->lru.pLruPrev = pGroup->lru.pLruNext = &pGroup->lru;
    }
    pCache->pGroup = pGroup;
    pCache->szPage = szPage;
    pCache->szExtra = szExtra;
    pCache->szAlloc = szPage + szExtra + ROUND8(sizeof(PgHdr1));
    pCache->bPurgeable = (bPurgeable ? 1 : 0);
    pcache1EnterMutex(pGroup);
    pcache1ResizeHash(pCache);
    if( bPurgeable ){
      pCache->nMin = 10;
      pGroup->nMinPage += pCache->nMin;
      pGroup->mxPinned = pGroup->nMaxPage + 10 - pGroup->nMinPage;
    }
    pcache1LeaveMutex(pGroup);
    if( pCache->nHash==0 ){
      pcache1Destroy((sqlite3_pcache*)pCache);
      pCache = 0;
    }
  }
  return (sqlite3_pcache *)pCache;
}