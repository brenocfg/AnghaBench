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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {scalar_t__ nPage; size_t szPage; TYPE_2__* pGroup; scalar_t__ bPurgeable; int /*<<< orphan*/  szAlloc; TYPE_3__* pFree; } ;
struct TYPE_8__ {TYPE_3__* pExtra; void* pBuf; } ;
struct TYPE_10__ {scalar_t__ isAnchor; scalar_t__ isBulkLocal; TYPE_1__ page; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {int /*<<< orphan*/  nCurrentPage; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ PgHdr1 ;
typedef  TYPE_4__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* pcache1Alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ pcache1InitBulk (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

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