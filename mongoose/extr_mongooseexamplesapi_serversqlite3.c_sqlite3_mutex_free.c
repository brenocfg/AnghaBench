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
struct TYPE_3__ {int /*<<< orphan*/  (* xMutexFree ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ mutex; } ;

/* Variables and functions */
 TYPE_2__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void sqlite3_mutex_free(sqlite3_mutex *p){
  if( p ){
    sqlite3GlobalConfig.mutex.xMutexFree(p);
  }
}