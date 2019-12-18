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
struct flock {int l_len; int l_pid; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
typedef  int ZCG ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_ERROR ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int getpid () ; 
 int /*<<< orphan*/  lock_file ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  tsrm_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zend_shared_alloc_lock_win32 () ; 
 int /*<<< orphan*/  zts_lock ; 

void zend_shared_alloc_lock(void)
{
#ifndef ZEND_WIN32
	struct flock mem_write_lock;

	mem_write_lock.l_type = F_WRLCK;
	mem_write_lock.l_whence = SEEK_SET;
	mem_write_lock.l_start = 0;
	mem_write_lock.l_len = 1;

#ifdef ZTS
	tsrm_mutex_lock(zts_lock);
#endif

#if 0
	/* this will happen once per process, and will un-globalize mem_write_lock */
	if (mem_write_lock.l_pid == -1) {
		mem_write_lock.l_pid = getpid();
	}
#endif

	while (1) {
		if (fcntl(lock_file, F_SETLKW, &mem_write_lock) == -1) {
			if (errno == EINTR) {
				continue;
			}
			zend_accel_error(ACCEL_LOG_ERROR, "Cannot create lock - %s (%d)", strerror(errno), errno);
		}
		break;
	}
#else
	zend_shared_alloc_lock_win32();
#endif

	ZCG(locked) = 1;
}