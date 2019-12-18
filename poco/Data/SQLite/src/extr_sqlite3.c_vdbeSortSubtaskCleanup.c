#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_8__ {scalar_t__ pFd; } ;
struct TYPE_7__ {scalar_t__ pFd; } ;
struct TYPE_9__ {scalar_t__ aMemory; int /*<<< orphan*/  pList; } ;
struct TYPE_10__ {TYPE_2__ file2; TYPE_1__ file; TYPE_3__ list; int /*<<< orphan*/  pUnpacked; } ;
typedef  TYPE_4__ SortSubtask ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OsCloseFree (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int /*<<< orphan*/  vdbeSorterRecordFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdbeSortSubtaskCleanup(sqlite3 *db, SortSubtask *pTask){
  sqlite3DbFree(db, pTask->pUnpacked);
#if SQLITE_MAX_WORKER_THREADS>0
  /* pTask->list.aMemory can only be non-zero if it was handed memory
  ** from the main thread.  That only occurs SQLITE_MAX_WORKER_THREADS>0 */
  if( pTask->list.aMemory ){
    sqlite3_free(pTask->list.aMemory);
  }else
#endif
  {
    assert( pTask->list.aMemory==0 );
    vdbeSorterRecordFree(0, pTask->list.pList);
  }
  if( pTask->file.pFd ){
    sqlite3OsCloseFree(pTask->file.pFd);
  }
  if( pTask->file2.pFd ){
    sqlite3OsCloseFree(pTask->file2.pFd);
  }
  memset(pTask, 0, sizeof(SortSubtask));
}