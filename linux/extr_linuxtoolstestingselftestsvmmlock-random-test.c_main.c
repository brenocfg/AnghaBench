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
 int /*<<< orphan*/  MLOCK_OUTOF_LIMIT_SIZE ; 
 int /*<<< orphan*/  MLOCK_RLIMIT_SIZE ; 
 int /*<<< orphan*/  MLOCK_WITHIN_LIMIT_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munlock (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ set_cap_limits (int /*<<< orphan*/ ) ; 
 int test_mlock_outof_limit (char*,int /*<<< orphan*/ ) ; 
 int test_mlock_within_limit (char*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	char *p = NULL;
	int ret = 0;

	if (set_cap_limits(MLOCK_RLIMIT_SIZE))
		return -1;

	p = malloc(MLOCK_WITHIN_LIMIT_SIZE);
	if (p == NULL) {
		perror("malloc() failure\n");
		return -1;
	}
	ret = test_mlock_within_limit(p, MLOCK_WITHIN_LIMIT_SIZE);
	if (ret)
		return ret;
	munlock(p, MLOCK_WITHIN_LIMIT_SIZE);
	free(p);


	p = malloc(MLOCK_OUTOF_LIMIT_SIZE);
	if (p == NULL) {
		perror("malloc() failure\n");
		return -1;
	}
	ret = test_mlock_outof_limit(p, MLOCK_OUTOF_LIMIT_SIZE);
	if (ret)
		return ret;
	munlock(p, MLOCK_OUTOF_LIMIT_SIZE);
	free(p);

	return 0;
}