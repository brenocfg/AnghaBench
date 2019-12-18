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
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_9__ {scalar_t__ nMax; scalar_t__ nMin; struct TYPE_9__* apHash; struct TYPE_9__* pBulk; scalar_t__ nPage; scalar_t__ bPurgeable; TYPE_1__* pGroup; } ;
struct TYPE_8__ {scalar_t__ nMaxPage; scalar_t__ nMinPage; scalar_t__ mxPinned; } ;
typedef  TYPE_1__ PGroup ;
typedef  TYPE_2__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcache1EnforceMaxPage (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  pcache1TruncateUnsafe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void pcache1Destroy(sqlite3_pcache *p){
  PCache1 *pCache = (PCache1 *)p;
  PGroup *pGroup = pCache->pGroup;
  assert( pCache->bPurgeable || (pCache->nMax==0 && pCache->nMin==0) );
  pcache1EnterMutex(pGroup);
  if( pCache->nPage ) pcache1TruncateUnsafe(pCache, 0);
  assert( pGroup->nMaxPage >= pCache->nMax );
  pGroup->nMaxPage -= pCache->nMax;
  assert( pGroup->nMinPage >= pCache->nMin );
  pGroup->nMinPage -= pCache->nMin;
  pGroup->mxPinned = pGroup->nMaxPage + 10 - pGroup->nMinPage;
  pcache1EnforceMaxPage(pCache);
  pcache1LeaveMutex(pGroup);
  sqlite3_free(pCache->pBulk);
  sqlite3_free(pCache->apHash);
  sqlite3_free(pCache);
}