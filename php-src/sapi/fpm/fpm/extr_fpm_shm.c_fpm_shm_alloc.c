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
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  errno ; 
 size_t fpm_shm_size ; 
 void* mmap (int /*<<< orphan*/ ,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,size_t,...) ; 

void *fpm_shm_alloc(size_t size) /* {{{ */
{
	void *mem;

	mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

#ifdef MAP_FAILED
	if (mem == MAP_FAILED) {
		zlog(ZLOG_SYSERROR, "unable to allocate %zu bytes in shared memory: %s", size, strerror(errno));
		return NULL;
	}
#endif

	if (!mem) {
		zlog(ZLOG_SYSERROR, "unable to allocate %zu bytes in shared memory", size);
		return NULL;
	}

	fpm_shm_size += size;
	return mem;
}