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
 char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int MCL_ONFAULT ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 unsigned long getpagesize () ; 
 scalar_t__ lock_check (char*) ; 
 scalar_t__ mlockall (int) ; 
 char* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munlockall () ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 scalar_t__ onfault_check (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int unlock_lock_check (char*) ; 
 scalar_t__ unlock_onfault_check (char*) ; 

__attribute__((used)) static int test_munlockall()
{
	char *map;
	int ret = 1;
	unsigned long page_size = getpagesize();

	map = mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (map == MAP_FAILED) {
		perror("test_munlockall mmap");
		goto out;
	}

	if (mlockall(MCL_CURRENT)) {
		perror("mlockall(MCL_CURRENT)");
		goto out;
	}

	if (lock_check(map))
		goto unmap;

	if (munlockall()) {
		perror("munlockall()");
		goto unmap;
	}

	if (unlock_lock_check(map))
		goto unmap;

	munmap(map, 2 * page_size);

	map = mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (map == MAP_FAILED) {
		perror("test_munlockall second mmap");
		goto out;
	}

	if (mlockall(MCL_CURRENT | MCL_ONFAULT)) {
		perror("mlockall(MCL_CURRENT | MCL_ONFAULT)");
		goto unmap;
	}

	if (onfault_check(map))
		goto unmap;

	if (munlockall()) {
		perror("munlockall()");
		goto unmap;
	}

	if (unlock_onfault_check(map))
		goto unmap;

	if (mlockall(MCL_CURRENT | MCL_FUTURE)) {
		perror("mlockall(MCL_CURRENT | MCL_FUTURE)");
		goto out;
	}

	if (lock_check(map))
		goto unmap;

	if (munlockall()) {
		perror("munlockall()");
		goto unmap;
	}

	ret = unlock_lock_check(map);

unmap:
	munmap(map, 2 * page_size);
out:
	munlockall();
	return ret;
}