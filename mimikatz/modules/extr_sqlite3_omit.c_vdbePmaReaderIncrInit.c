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
struct TYPE_6__ {scalar_t__ bUseThread; int /*<<< orphan*/  pTask; } ;
struct TYPE_5__ {TYPE_2__* pIncr; } ;
typedef  TYPE_1__ PmaReader ;
typedef  TYPE_2__ IncrMerger ;

/* Variables and functions */
 int INCRINIT_TASK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vdbePmaReaderBgIncrInit ; 
 int vdbePmaReaderIncrMergeInit (TYPE_1__*,int) ; 
 int vdbeSorterCreateThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int vdbePmaReaderIncrInit(PmaReader *pReadr, int eMode){
  IncrMerger *pIncr = pReadr->pIncr;   /* Incremental merger */
  int rc = SQLITE_OK;                  /* Return code */
  if( pIncr ){
#if SQLITE_MAX_WORKER_THREADS>0
    assert( pIncr->bUseThread==0 || eMode==INCRINIT_TASK );
    if( pIncr->bUseThread ){
      void *pCtx = (void*)pReadr;
      rc = vdbeSorterCreateThread(pIncr->pTask, vdbePmaReaderBgIncrInit, pCtx);
    }else
#endif
    {
      rc = vdbePmaReaderIncrMergeInit(pReadr, eMode);
    }
  }
  return rc;
}