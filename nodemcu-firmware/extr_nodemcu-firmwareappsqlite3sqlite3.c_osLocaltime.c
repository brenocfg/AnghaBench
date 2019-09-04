#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_2__ {scalar_t__ bLocaltimeFault; } ;

/* Variables and functions */
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex ; 
 TYPE_1__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osLocaltime(time_t *t, struct tm *pTm){
  int rc;
#if !HAVE_LOCALTIME_R && !HAVE_LOCALTIME_S
  struct tm *pX;
#if SQLITE_THREADSAFE>0
  sqlite3_mutex *mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
#endif
  sqlite3_mutex_enter(mutex);
  pX = localtime(t);
#ifndef SQLITE_UNTESTABLE
  if( sqlite3GlobalConfig.bLocaltimeFault ) pX = 0;
#endif
  if( pX ) *pTm = *pX;
  sqlite3_mutex_leave(mutex);
  rc = pX==0;
#else
#ifndef SQLITE_UNTESTABLE
  if( sqlite3GlobalConfig.bLocaltimeFault ) return 1;
#endif
#if HAVE_LOCALTIME_R
  rc = localtime_r(t, pTm)==0;
#else
  rc = localtime_s(pTm, t);
#endif /* HAVE_LOCALTIME_R */
#endif /* HAVE_LOCALTIME_R || HAVE_LOCALTIME_S */
  return rc;
}