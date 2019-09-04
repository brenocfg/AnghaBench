#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bUsePMA; int /*<<< orphan*/  list; int /*<<< orphan*/ * aTask; } ;
typedef  TYPE_1__ VdbeSorter ;

/* Variables and functions */
 int vdbeSorterListToPMA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbeSorterFlushPMA(VdbeSorter *pSorter){
#if SQLITE_MAX_WORKER_THREADS==0
  pSorter->bUsePMA = 1;
  return vdbeSorterListToPMA(&pSorter->aTask[0], &pSorter->list);
#else
  int rc = SQLITE_OK;
  int i;
  SortSubtask *pTask = 0;    /* Thread context used to create new PMA */
  int nWorker = (pSorter->nTask-1);

  /* Set the flag to indicate that at least one PMA has been written.
  ** Or will be, anyhow.  */
  pSorter->bUsePMA = 1;

  /* Select a sub-task to sort and flush the current list of in-memory
  ** records to disk. If the sorter is running in multi-threaded mode,
  ** round-robin between the first (pSorter->nTask-1) tasks. Except, if
  ** the background thread from a sub-tasks previous turn is still running,
  ** skip it. If the first (pSorter->nTask-1) sub-tasks are all still busy,
  ** fall back to using the final sub-task. The first (pSorter->nTask-1)
  ** sub-tasks are prefered as they use background threads - the final
  ** sub-task uses the main thread. */
  for(i=0; i<nWorker; i++){
    int iTest = (pSorter->iPrev + i + 1) % nWorker;
    pTask = &pSorter->aTask[iTest];
    if( pTask->bDone ){
      rc = vdbeSorterJoinThread(pTask);
    }
    if( rc!=SQLITE_OK || pTask->pThread==0 ) break;
  }

  if( rc==SQLITE_OK ){
    if( i==nWorker ){
      /* Use the foreground thread for this operation */
      rc = vdbeSorterListToPMA(&pSorter->aTask[nWorker], &pSorter->list);
    }else{
      /* Launch a background thread for this operation */
      u8 *aMem = pTask->list.aMemory;
      void *pCtx = (void*)pTask;

      assert( pTask->pThread==0 && pTask->bDone==0 );
      assert( pTask->list.pList==0 );
      assert( pTask->list.aMemory==0 || pSorter->list.aMemory!=0 );

      pSorter->iPrev = (u8)(pTask - pSorter->aTask);
      pTask->list = pSorter->list;
      pSorter->list.pList = 0;
      pSorter->list.szPMA = 0;
      if( aMem ){
        pSorter->list.aMemory = aMem;
        pSorter->nMemory = sqlite3MallocSize(aMem);
      }else if( pSorter->list.aMemory ){
        pSorter->list.aMemory = sqlite3Malloc(pSorter->nMemory);
        if( !pSorter->list.aMemory ) return SQLITE_NOMEM_BKPT;
      }

      rc = vdbeSorterCreateThread(pTask, vdbeSorterFlushThread, pCtx);
    }
  }

  return rc;
#endif /* SQLITE_MAX_WORKER_THREADS!=0 */
}