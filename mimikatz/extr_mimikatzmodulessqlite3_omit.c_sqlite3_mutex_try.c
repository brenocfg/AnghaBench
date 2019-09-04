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
struct TYPE_3__ {int (* xMutexTry ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ mutex; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int (*) (int /*<<< orphan*/ *)) ; 
 TYPE_2__ sqlite3GlobalConfig ; 
 int stub1 (int /*<<< orphan*/ *) ; 

int sqlite3_mutex_try(sqlite3_mutex *p){
  int rc = SQLITE_OK;
  if( p ){
    assert( sqlite3GlobalConfig.mutex.xMutexTry );
    return sqlite3GlobalConfig.mutex.xMutexTry(p);
  }
  return rc;
}