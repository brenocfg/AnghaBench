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

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 size_t fpm_shm_size ; 
 int munmap (void*,size_t) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

int fpm_shm_free(void *mem, size_t size) /* {{{ */
{
	if (!mem) {
		zlog(ZLOG_ERROR, "mem is NULL");
		return 0;
	}

	if (munmap(mem, size) == -1) {
		zlog(ZLOG_SYSERROR, "Unable to free shm");
		return 0;
	}

	if (fpm_shm_size - size > 0) {
		fpm_shm_size -= size;
	} else {
		fpm_shm_size = 0;
	}

	return 1;
}