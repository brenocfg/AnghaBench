#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ alarmCallback; int alarmThreshold; int nearlyFull; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int (* xRoundup ) (int) ;void* (* xMalloc ) (int) ;} ;
struct TYPE_5__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_COUNT ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MEMORY_USED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ mem0 ; 
 TYPE_2__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3MallocAlarm (int) ; 
 int sqlite3MallocSize (void*) ; 
 int /*<<< orphan*/  sqlite3StatusAdd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3StatusSet (int /*<<< orphan*/ ,int) ; 
 int sqlite3StatusValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int stub1 (int) ; 
 void* stub2 (int) ; 
 void* stub3 (int) ; 

__attribute__((used)) static int mallocWithAlarm(int n, void **pp){
  int nFull;
  void *p;
  assert( sqlite3_mutex_held(mem0.mutex) );
  nFull = sqlite3GlobalConfig.m.xRoundup(n);
  sqlite3StatusSet(SQLITE_STATUS_MALLOC_SIZE, n);
  if( mem0.alarmCallback!=0 ){
    int nUsed = sqlite3StatusValue(SQLITE_STATUS_MEMORY_USED);
    if( nUsed >= mem0.alarmThreshold - nFull ){
      mem0.nearlyFull = 1;
      sqlite3MallocAlarm(nFull);
    }else{
      mem0.nearlyFull = 0;
    }
  }
  p = sqlite3GlobalConfig.m.xMalloc(nFull);
#ifdef SQLITE_ENABLE_MEMORY_MANAGEMENT
  if( p==0 && mem0.alarmCallback ){
    sqlite3MallocAlarm(nFull);
    p = sqlite3GlobalConfig.m.xMalloc(nFull);
  }
#endif
  if( p ){
    nFull = sqlite3MallocSize(p);
    sqlite3StatusAdd(SQLITE_STATUS_MEMORY_USED, nFull);
    sqlite3StatusAdd(SQLITE_STATUS_MALLOC_COUNT, 1);
  }
  *pp = p;
  return nFull;
}