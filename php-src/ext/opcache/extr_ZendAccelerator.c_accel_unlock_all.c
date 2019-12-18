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
struct flock {scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_DEBUG ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  accel_deactivate_sub () ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  lock_file ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void accel_unlock_all(void)
{
#ifdef ZEND_WIN32
	accel_deactivate_sub();
#else
	struct flock mem_usage_unlock_all;

	mem_usage_unlock_all.l_type = F_UNLCK;
	mem_usage_unlock_all.l_whence = SEEK_SET;
	mem_usage_unlock_all.l_start = 0;
	mem_usage_unlock_all.l_len = 0;

	if (fcntl(lock_file, F_SETLK, &mem_usage_unlock_all) == -1) {
		zend_accel_error(ACCEL_LOG_DEBUG, "UnlockAll:  %s (%d)", strerror(errno), errno);
	}
#endif
}