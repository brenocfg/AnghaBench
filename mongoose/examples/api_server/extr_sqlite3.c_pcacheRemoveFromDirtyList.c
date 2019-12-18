#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pDirty; TYPE_1__* pDirtyTail; TYPE_1__* pSynced; } ;
struct TYPE_5__ {int flags; struct TYPE_5__* pDirtyPrev; struct TYPE_5__* pDirtyNext; TYPE_2__* pCache; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ PCache ;

/* Variables and functions */
 int PGHDR_NEED_SYNC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  expensive_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcacheCheckSynced (TYPE_2__*) ; 

__attribute__((used)) static void pcacheRemoveFromDirtyList(PgHdr *pPage){
  PCache *p = pPage->pCache;

  assert( pPage->pDirtyNext || pPage==p->pDirtyTail );
  assert( pPage->pDirtyPrev || pPage==p->pDirty );

  /* Update the PCache1.pSynced variable if necessary. */
  if( p->pSynced==pPage ){
    PgHdr *pSynced = pPage->pDirtyPrev;
    while( pSynced && (pSynced->flags&PGHDR_NEED_SYNC) ){
      pSynced = pSynced->pDirtyPrev;
    }
    p->pSynced = pSynced;
  }

  if( pPage->pDirtyNext ){
    pPage->pDirtyNext->pDirtyPrev = pPage->pDirtyPrev;
  }else{
    assert( pPage==p->pDirtyTail );
    p->pDirtyTail = pPage->pDirtyPrev;
  }
  if( pPage->pDirtyPrev ){
    pPage->pDirtyPrev->pDirtyNext = pPage->pDirtyNext;
  }else{
    assert( pPage==p->pDirty );
    p->pDirty = pPage->pDirtyNext;
  }
  pPage->pDirtyNext = 0;
  pPage->pDirtyPrev = 0;

  expensive_assert( pcacheCheckSynced(p) );
}