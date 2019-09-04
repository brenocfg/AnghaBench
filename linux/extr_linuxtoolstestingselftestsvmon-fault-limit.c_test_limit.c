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
struct rlimit {int rlim_max; } ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_POPULATE ; 
 int MAP_PRIVATE ; 
 int MCL_FUTURE ; 
 int MCL_ONFAULT ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 scalar_t__ mlockall (int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munlockall () ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int test_limit(void)
{
	int ret = 1;
	struct rlimit lims;
	void *map;

	if (getrlimit(RLIMIT_MEMLOCK, &lims)) {
		perror("getrlimit");
		return ret;
	}

	if (mlockall(MCL_ONFAULT | MCL_FUTURE)) {
		perror("mlockall");
		return ret;
	}

	map = mmap(NULL, 2 * lims.rlim_max, PROT_READ | PROT_WRITE,
		   MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE, -1, 0);
	if (map != MAP_FAILED)
		printf("mmap should have failed, but didn't\n");
	else {
		ret = 0;
		munmap(map, 2 * lims.rlim_max);
	}

	munlockall();
	return ret;
}