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
 int execve (char*,char* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void run_exec(void)
{
	char *const argv[] = { "./exec_target", NULL };

	if (execve("./exec_target", argv, NULL) == -1) {
		perror("execve");
		exit(1);
	}
}