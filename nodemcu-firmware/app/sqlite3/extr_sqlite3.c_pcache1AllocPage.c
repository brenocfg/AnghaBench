#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_16__ {int /*<<< orphan*/  nCurrentPage; int /*<<< orphan*/  mutex; } ;
struct TYPE_15__ {scalar_t__ nPage; size_t szPage; size_t szAlloc; TYPE_6__* pGroup; scalar_t__ bPurgeable; scalar_t__ szExtra; TYPE_2__* pFree; } ;
struct TYPE_13__ {TYPE_2__* pExtra; void* pBuf; } ;
struct TYPE_14__ {scalar_t__ isAnchor; scalar_t__ isBulkLocal; TYPE_1__ page; struct TYPE_14__* pNext; } ;
struct TYPE_12__ {scalar_t__ separateCache; TYPE_6__ grp; } ;
typedef  TYPE_2__ PgHdr1 ;
typedef  TYPE_3__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_11__ pcache1 ; 
 void* pcache1Alloc (size_t) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_6__*) ; 
 int /*<<< orphan*/  pcache1Free (void*) ; 
 scalar_t__ pcache1InitBulk (TYPE_3__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 TYPE_2__* sqlite3Malloc (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PgHdr1 *pcache1AllocPage(PCache1 *pCache, int benignMalloc){
  PgHdr1 *p = 0;
  void *pPg;

  assert( sqlite3_mutex_held(pCache->pGroup->mutex) );
  if( pCache->pFree || (pCache->nPage==0 && pcache1InitBulk(pCache)) ){
    p = pCache->pFree;
    pCache->pFree = p->pNext;
    p->pNext = 0;
  }else{
#ifdef SQLITE_ENABLE_MEMORY_MANAGEMENT
    /* The group mutex must be released before pcache1Alloc() is called. This
    ** is because it might call sqlite3_release_memory(), which assumes that
    ** this mutex is not held. */
    assert( pcache1.separateCache==0 );
    assert( pCache->pGroup==&pcache1.grp );
    pcache1LeaveMutex(pCache->pGroup);
#endif
    if( benignMalloc ){ sqlite3BeginBenignMalloc(); }
#ifdef SQLITE_PCACHE_SEPARATE_HEADER
    pPg = pcache1Alloc(pCache->szPage);
    p = sqlite3Malloc(sizeof(PgHdr1) + pCache->szExtra);
    if( !pPg || !p ){
      pcache1Free(pPg);
      sqlite3_free(p);
      pPg = 0;
    }
#else
    pPg = pcache1Alloc(pCache->szAlloc);
    p = (PgHdr1 *)&((u8 *)pPg)[pCache->szPage];
#endif
    if( benignMalloc ){ sqlite3EndBenignMalloc(); }
#ifdef SQLITE_ENABLE_MEMORY_MANAGEMENT
    pcache1EnterMutex(pCache->pGroup);
#endif
    if( pPg==0 ) return 0;
    p->page.pBuf = pPg;
    p->page.pExtra = &p[1];
    p->isBulkLocal = 0;
    p->isAnchor = 0;
  }
  if( pCache->bPurgeable ){
    pCache->pGroup->nCurrentPage++;
  }
  return p;
}