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
struct TYPE_4__ {int /*<<< orphan*/ * pMerger; int /*<<< orphan*/ * aTask; } ;
typedef  TYPE_1__ VdbeSorter ;
typedef  int /*<<< orphan*/  SortSubtask ;
typedef  int /*<<< orphan*/  MergeEngine ;

/* Variables and functions */
 int /*<<< orphan*/  INCRINIT_NORMAL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  vdbeMergeEngineFree (int /*<<< orphan*/ *) ; 
 int vdbeMergeEngineInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vdbeSorterMergeTreeBuild (TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int vdbeSorterSetupMerge(VdbeSorter *pSorter){
  int rc;                         /* Return code */
  SortSubtask *pTask0 = &pSorter->aTask[0];
  MergeEngine *pMain = 0;
#if SQLITE_MAX_WORKER_THREADS
  sqlite3 *db = pTask0->pSorter->db;
  int i;
  SorterCompare xCompare = vdbeSorterGetCompare(pSorter);
  for(i=0; i<pSorter->nTask; i++){
    pSorter->aTask[i].xCompare = xCompare;
  }
#endif

  rc = vdbeSorterMergeTreeBuild(pSorter, &pMain);
  if( rc==SQLITE_OK ){
#if SQLITE_MAX_WORKER_THREADS
    assert( pSorter->bUseThreads==0 || pSorter->nTask>1 );
    if( pSorter->bUseThreads ){
      int iTask;
      PmaReader *pReadr = 0;
      SortSubtask *pLast = &pSorter->aTask[pSorter->nTask-1];
      rc = vdbeSortAllocUnpacked(pLast);
      if( rc==SQLITE_OK ){
        pReadr = (PmaReader*)sqlite3DbMallocZero(db, sizeof(PmaReader));
        pSorter->pReader = pReadr;
        if( pReadr==0 ) rc = SQLITE_NOMEM_BKPT;
      }
      if( rc==SQLITE_OK ){
        rc = vdbeIncrMergerNew(pLast, pMain, &pReadr->pIncr);
        if( rc==SQLITE_OK ){
          vdbeIncrMergerSetThreads(pReadr->pIncr);
          for(iTask=0; iTask<(pSorter->nTask-1); iTask++){
            IncrMerger *pIncr;
            if( (pIncr = pMain->aReadr[iTask].pIncr) ){
              vdbeIncrMergerSetThreads(pIncr);
              assert( pIncr->pTask!=pLast );
            }
          }
          for(iTask=0; rc==SQLITE_OK && iTask<pSorter->nTask; iTask++){
            /* Check that:
            **
            **   a) The incremental merge object is configured to use the
            **      right task, and
            **   b) If it is using task (nTask-1), it is configured to run
            **      in single-threaded mode. This is important, as the
            **      root merge (INCRINIT_ROOT) will be using the same task
            **      object.
            */
            PmaReader *p = &pMain->aReadr[iTask];
            assert( p->pIncr==0 || (
                (p->pIncr->pTask==&pSorter->aTask[iTask])             /* a */
             && (iTask!=pSorter->nTask-1 || p->pIncr->bUseThread==0)  /* b */
            ));
            rc = vdbePmaReaderIncrInit(p, INCRINIT_TASK);
          }
        }
        pMain = 0;
      }
      if( rc==SQLITE_OK ){
        rc = vdbePmaReaderIncrMergeInit(pReadr, INCRINIT_ROOT);
      }
    }else
#endif
    {
      rc = vdbeMergeEngineInit(pTask0, pMain, INCRINIT_NORMAL);
      pSorter->pMerger = pMain;
      pMain = 0;
    }
  }

  if( rc!=SQLITE_OK ){
    vdbeMergeEngineFree(pMain);
  }
  return rc;
}