#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nCurrentPage; scalar_t__ nMaxPage; TYPE_2__* pLruTail; int /*<<< orphan*/  mutex; } ;
struct TYPE_9__ {TYPE_1__* pCache; } ;
struct TYPE_8__ {TYPE_3__* pGroup; } ;
typedef  TYPE_2__ PgHdr1 ;
typedef  TYPE_3__ PGroup ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcache1FreePage (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1PinPage (TYPE_2__*) ; 
 int /*<<< orphan*/  pcache1RemoveFromHash (TYPE_2__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcache1EnforceMaxPage(PGroup *pGroup){
  assert( sqlite3_mutex_held(pGroup->mutex) );
  while( pGroup->nCurrentPage>pGroup->nMaxPage && pGroup->pLruTail ){
    PgHdr1 *p = pGroup->pLruTail;
    assert( p->pCache->pGroup==pGroup );
    pcache1PinPage(p);
    pcache1RemoveFromHash(p);
    pcache1FreePage(p);
  }
}