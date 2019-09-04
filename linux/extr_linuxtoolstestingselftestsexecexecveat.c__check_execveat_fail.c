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
 int /*<<< orphan*/  argv ; 
 int /*<<< orphan*/  envp ; 
 int errno ; 
 int execveat_ (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int) ; 

__attribute__((used)) static int _check_execveat_fail(int fd, const char *path, int flags,
				int expected_errno, const char *errno_str)
{
	int rc;

	errno = 0;
	printf("Check failure of execveat(%d, '%s', %d) with %s... ",
		fd, path?:"(null)", flags, errno_str);
	rc = execveat_(fd, path, argv, envp, flags);

	if (rc > 0) {
		printf("[FAIL] (unexpected success from execveat(2))\n");
		return 1;
	}
	if (errno != expected_errno) {
		printf("[FAIL] (expected errno %d (%s) not %d (%s)\n",
			expected_errno, strerror(expected_errno),
			errno, strerror(errno));
		return 1;
	}
	printf("[OK]\n");
	return 0;
}