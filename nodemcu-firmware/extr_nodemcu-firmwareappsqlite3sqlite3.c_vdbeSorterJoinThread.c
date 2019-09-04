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
struct TYPE_4__ {int bDone; scalar_t__ pThread; } ;
typedef  TYPE_1__ SortSubtask ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ERROR ; 
 void* SQLITE_INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int SQLITE_PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bDone ; 
 int /*<<< orphan*/  sqlite3ThreadJoin (scalar_t__,void**) ; 
 int /*<<< orphan*/  vdbeSorterBlockDebug (TYPE_1__*,int,char*) ; 

__attribute__((used)) static int vdbeSorterJoinThread(SortSubtask *pTask){
  int rc = SQLITE_OK;
  if( pTask->pThread ){
#ifdef SQLITE_DEBUG_SORTER_THREADS
    int bDone = pTask->bDone;
#endif
    void *pRet = SQLITE_INT_TO_PTR(SQLITE_ERROR);
    vdbeSorterBlockDebug(pTask, !bDone, "enter");
    (void)sqlite3ThreadJoin(pTask->pThread, &pRet);
    vdbeSorterBlockDebug(pTask, !bDone, "exit");
    rc = SQLITE_PTR_TO_INT(pRet);
    assert( pTask->bDone==1 );
    pTask->bDone = 0;
    pTask->pThread = 0;
  }
  return rc;
}