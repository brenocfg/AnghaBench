#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_mutex ;
struct TYPE_3__ {int /*<<< orphan*/ * (* xMutexAlloc ) (int) ;} ;
struct TYPE_4__ {TYPE_1__ mutex; } ;

/* Variables and functions */
 int SQLITE_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ * (*) (int)) ; 
 TYPE_2__ sqlite3GlobalConfig ; 
 scalar_t__ sqlite3MutexInit () ; 
 scalar_t__ sqlite3_initialize () ; 
 int /*<<< orphan*/ * stub1 (int) ; 

sqlite3_mutex *sqlite3_mutex_alloc(int id){
#ifndef SQLITE_OMIT_AUTOINIT
  if( id<=SQLITE_MUTEX_RECURSIVE && sqlite3_initialize() ) return 0;
  if( id>SQLITE_MUTEX_RECURSIVE && sqlite3MutexInit() ) return 0;
#endif
  assert( sqlite3GlobalConfig.mutex.xMutexAlloc );
  return sqlite3GlobalConfig.mutex.xMutexAlloc(id);
}