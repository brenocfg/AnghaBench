#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_17__ {int nTask; TYPE_3__* aTask; scalar_t__ bUseThreads; } ;
typedef  TYPE_2__ VdbeSorter ;
struct TYPE_19__ {TYPE_1__* aReadr; } ;
struct TYPE_18__ {scalar_t__ nPMA; } ;
struct TYPE_16__ {int /*<<< orphan*/  pIncr; } ;
typedef  TYPE_3__ SortSubtask ;
typedef  TYPE_4__ MergeEngine ;

/* Variables and functions */
 int MIN (int,int) ; 
 int SORTER_MAX_MERGE_COUNT ; 
 scalar_t__ SQLITE_MAX_WORKER_THREADS ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int vdbeIncrMergerNew (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdbeMergeEngineFree (TYPE_4__*) ; 
 int vdbeMergeEngineLevel0 (TYPE_3__*,int,int /*<<< orphan*/ *,TYPE_4__**) ; 
 TYPE_4__* vdbeMergeEngineNew (int) ; 
 int vdbeSorterAddToTree (TYPE_3__*,int,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 int vdbeSorterTreeDepth (scalar_t__) ; 

__attribute__((used)) static int vdbeSorterMergeTreeBuild(
  VdbeSorter *pSorter,       /* The VDBE cursor that implements the sort */
  MergeEngine **ppOut        /* Write the MergeEngine here */
){
  MergeEngine *pMain = 0;
  int rc = SQLITE_OK;
  int iTask;

#if SQLITE_MAX_WORKER_THREADS>0
  /* If the sorter uses more than one task, then create the top-level
  ** MergeEngine here. This MergeEngine will read data from exactly
  ** one PmaReader per sub-task.  */
  assert( pSorter->bUseThreads || pSorter->nTask==1 );
  if( pSorter->nTask>1 ){
    pMain = vdbeMergeEngineNew(pSorter->nTask);
    if( pMain==0 ) rc = SQLITE_NOMEM_BKPT;
  }
#endif

  for(iTask=0; rc==SQLITE_OK && iTask<pSorter->nTask; iTask++){
    SortSubtask *pTask = &pSorter->aTask[iTask];
    assert( pTask->nPMA>0 || SQLITE_MAX_WORKER_THREADS>0 );
    if( SQLITE_MAX_WORKER_THREADS==0 || pTask->nPMA ){
      MergeEngine *pRoot = 0;     /* Root node of tree for this task */
      int nDepth = vdbeSorterTreeDepth(pTask->nPMA);
      i64 iReadOff = 0;

      if( pTask->nPMA<=SORTER_MAX_MERGE_COUNT ){
        rc = vdbeMergeEngineLevel0(pTask, pTask->nPMA, &iReadOff, &pRoot);
      }else{
        int i;
        int iSeq = 0;
        pRoot = vdbeMergeEngineNew(SORTER_MAX_MERGE_COUNT);
        if( pRoot==0 ) rc = SQLITE_NOMEM_BKPT;
        for(i=0; i<pTask->nPMA && rc==SQLITE_OK; i += SORTER_MAX_MERGE_COUNT){
          MergeEngine *pMerger = 0; /* New level-0 PMA merger */
          int nReader;              /* Number of level-0 PMAs to merge */

          nReader = MIN(pTask->nPMA - i, SORTER_MAX_MERGE_COUNT);
          rc = vdbeMergeEngineLevel0(pTask, nReader, &iReadOff, &pMerger);
          if( rc==SQLITE_OK ){
            rc = vdbeSorterAddToTree(pTask, nDepth, iSeq++, pRoot, pMerger);
          }
        }
      }

      if( rc==SQLITE_OK ){
#if SQLITE_MAX_WORKER_THREADS>0
        if( pMain!=0 ){
          rc = vdbeIncrMergerNew(pTask, pRoot, &pMain->aReadr[iTask].pIncr);
        }else
#endif
        {
          assert( pMain==0 );
          pMain = pRoot;
        }
      }else{
        vdbeMergeEngineFree(pRoot);
      }
    }
  }

  if( rc!=SQLITE_OK ){
    vdbeMergeEngineFree(pMain);
    pMain = 0;
  }
  *ppOut = pMain;
  return rc;
}