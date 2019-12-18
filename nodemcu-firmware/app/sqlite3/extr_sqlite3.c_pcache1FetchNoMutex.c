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
struct TYPE_9__ {unsigned int nHash; TYPE_1__** apHash; } ;
struct TYPE_8__ {unsigned int iKey; int /*<<< orphan*/  isPinned; struct TYPE_8__* pNext; } ;
typedef  TYPE_1__ PgHdr1 ;
typedef  TYPE_2__ PCache1 ;

/* Variables and functions */
 TYPE_1__* pcache1FetchStage2 (TYPE_2__*,unsigned int,int) ; 
 TYPE_1__* pcache1PinPage (TYPE_1__*) ; 

__attribute__((used)) static PgHdr1 *pcache1FetchNoMutex(
  sqlite3_pcache *p,
  unsigned int iKey,
  int createFlag
){
  PCache1 *pCache = (PCache1 *)p;
  PgHdr1 *pPage = 0;

  /* Step 1: Search the hash table for an existing entry. */
  pPage = pCache->apHash[iKey % pCache->nHash];
  while( pPage && pPage->iKey!=iKey ){ pPage = pPage->pNext; }

  /* Step 2: If the page was found in the hash table, then return it.
  ** If the page was not in the hash table and createFlag is 0, abort.
  ** Otherwise (page not in hash and createFlag!=0) continue with
  ** subsequent steps to try to create the page. */
  if( pPage ){
    if( !pPage->isPinned ){
      return pcache1PinPage(pPage);
    }else{
      return pPage;
    }
  }else if( createFlag ){
    /* Steps 3, 4, and 5 implemented by this subroutine */
    return pcache1FetchStage2(pCache, iKey, createFlag);
  }else{
    return 0;
  }
}