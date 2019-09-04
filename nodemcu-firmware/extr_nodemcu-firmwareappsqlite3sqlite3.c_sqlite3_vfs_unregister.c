#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfsUnlink (int /*<<< orphan*/ *) ; 

int sqlite3_vfs_unregister(sqlite3_vfs *pVfs){
#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
#endif
  sqlite3_mutex_enter(mutex);
  vfsUnlink(pVfs);
  sqlite3_mutex_leave(mutex);
  return SQLITE_OK;
}