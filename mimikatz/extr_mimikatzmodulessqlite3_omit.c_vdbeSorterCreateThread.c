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
struct TYPE_3__ {scalar_t__ pThread; scalar_t__ bDone; } ;
typedef  TYPE_1__ SortSubtask ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ThreadCreate (scalar_t__*,void* (*) (void*),void*) ; 

__attribute__((used)) static int vdbeSorterCreateThread(
  SortSubtask *pTask,             /* Thread will use this task object */
  void *(*xTask)(void*),          /* Routine to run in a separate thread */
  void *pIn                       /* Argument passed into xTask() */
){
  assert( pTask->pThread==0 && pTask->bDone==0 );
  return sqlite3ThreadCreate(&pTask->pThread, xTask, pIn);
}