#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pMerger; } ;
typedef  TYPE_1__ IncrMerger ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vdbeMergeEngineFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdbeIncrFree(IncrMerger *pIncr){
  if( pIncr ){
#if SQLITE_MAX_WORKER_THREADS>0
    if( pIncr->bUseThread ){
      vdbeSorterJoinThread(pIncr->pTask);
      if( pIncr->aFile[0].pFd ) sqlite3OsCloseFree(pIncr->aFile[0].pFd);
      if( pIncr->aFile[1].pFd ) sqlite3OsCloseFree(pIncr->aFile[1].pFd);
    }
#endif
    vdbeMergeEngineFree(pIncr->pMerger);
    sqlite3_free(pIncr);
  }
}