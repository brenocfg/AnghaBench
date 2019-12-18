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
struct flock {int l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
typedef  int /*<<< orphan*/  ZCG ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_ERROR ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  lock_file ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsrm_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_shared_alloc_unlock_win32 () ; 
 int /*<<< orphan*/  zts_lock ; 

void zend_shared_alloc_unlock(void)
{
#ifndef ZEND_WIN32
	struct flock mem_write_unlock;

	mem_write_unlock.l_type = F_UNLCK;
	mem_write_unlock.l_whence = SEEK_SET;
	mem_write_unlock.l_start = 0;
	mem_write_unlock.l_len = 1;
#endif

	ZCG(locked) = 0;

#ifndef ZEND_WIN32
	if (fcntl(lock_file, F_SETLK, &mem_write_unlock) == -1) {
		zend_accel_error(ACCEL_LOG_ERROR, "Cannot remove lock - %s (%d)", strerror(errno), errno);
	}
#ifdef ZTS
	tsrm_mutex_unlock(zts_lock);
#endif
#else
	zend_shared_alloc_unlock_win32();
#endif
}