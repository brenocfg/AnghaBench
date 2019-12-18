#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* pRecord; } ;
typedef  TYPE_1__ VdbeSorter ;
struct TYPE_11__ {TYPE_1__* pSorter; } ;
typedef  TYPE_2__ VdbeCursor ;
struct TYPE_12__ {struct TYPE_12__* pNext; } ;
typedef  TYPE_3__ SorterRecord ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3MallocZero (int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__**) ; 
 int /*<<< orphan*/  vdbeSorterMerge (TYPE_2__ const*,TYPE_3__*,TYPE_3__*,TYPE_3__**) ; 

__attribute__((used)) static int vdbeSorterSort(const VdbeCursor *pCsr){
  int i;
  SorterRecord **aSlot;
  SorterRecord *p;
  VdbeSorter *pSorter = pCsr->pSorter;

  aSlot = (SorterRecord **)sqlite3MallocZero(64 * sizeof(SorterRecord *));
  if( !aSlot ){
    return SQLITE_NOMEM;
  }

  p = pSorter->pRecord;
  while( p ){
    SorterRecord *pNext = p->pNext;
    p->pNext = 0;
    for(i=0; aSlot[i]; i++){
      vdbeSorterMerge(pCsr, p, aSlot[i], &p);
      aSlot[i] = 0;
    }
    aSlot[i] = p;
    p = pNext;
  }

  p = 0;
  for(i=0; i<64; i++){
    vdbeSorterMerge(pCsr, p, aSlot[i], &p);
  }
  pSorter->pRecord = p;

  sqlite3_free(aSlot);
  return SQLITE_OK;
}