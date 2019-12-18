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
struct TYPE_3__ {int nTask; int /*<<< orphan*/ * aTask; } ;
typedef  TYPE_1__ VdbeSorter ;
typedef  int /*<<< orphan*/  SortSubtask ;

/* Variables and functions */
 int SQLITE_OK ; 
 int vdbeSorterJoinThread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbeSorterJoinAll(VdbeSorter *pSorter, int rcin){
  int rc = rcin;
  int i;

  /* This function is always called by the main user thread.
  **
  ** If this function is being called after SorterRewind() has been called,
  ** it is possible that thread pSorter->aTask[pSorter->nTask-1].pThread
  ** is currently attempt to join one of the other threads. To avoid a race
  ** condition where this thread also attempts to join the same object, join
  ** thread pSorter->aTask[pSorter->nTask-1].pThread first. */
  for(i=pSorter->nTask-1; i>=0; i--){
    SortSubtask *pTask = &pSorter->aTask[i];
    int rc2 = vdbeSorterJoinThread(pTask);
    if( rc==SQLITE_OK ) rc = rc2;
  }
  return rc;
}