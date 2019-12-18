#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pInSavepoint; } ;
struct TYPE_4__ {int nSavepoint; scalar_t__ nSubRec; TYPE_2__* aSavepoint; int /*<<< orphan*/  sjfd; int /*<<< orphan*/  exclusiveMode; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3BitvecDestroy (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3JournalIsInMemory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void releaseAllSavepoints(Pager *pPager){
  int ii;               /* Iterator for looping through Pager.aSavepoint */
  for(ii=0; ii<pPager->nSavepoint; ii++){
    sqlite3BitvecDestroy(pPager->aSavepoint[ii].pInSavepoint);
  }
  if( !pPager->exclusiveMode || sqlite3JournalIsInMemory(pPager->sjfd) ){
    sqlite3OsClose(pPager->sjfd);
  }
  sqlite3_free(pPager->aSavepoint);
  pPager->aSavepoint = 0;
  pPager->nSavepoint = 0;
  pPager->nSubRec = 0;
}