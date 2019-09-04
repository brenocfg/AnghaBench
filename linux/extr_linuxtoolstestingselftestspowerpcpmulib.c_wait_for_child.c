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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int wait_for_child(pid_t child_pid)
{
	int rc;

	if (waitpid(child_pid, &rc, 0) == -1) {
		perror("waitpid");
		return 1;
	}

	if (WIFEXITED(rc))
		rc = WEXITSTATUS(rc);
	else
		rc = 1; /* Signal or other */

	return rc;
}