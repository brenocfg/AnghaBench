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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  debug (char*,int,...) ; 
 int proc_read_text (int,char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static int proc_check_stopped(int pid)
{
	char buf[PAGE_SIZE];
	int len;

	len = proc_read_text(pid, "stat", buf, sizeof(buf));
	if (len == -1) {
		debug("Can't get %d stat\n", pid);
		return -1;
	}

	if (strstr(buf, "(test_freezer) T ") == NULL) {
		debug("Process %d in the unexpected state: %s\n", pid, buf);
		return -1;
	}

	return 0;
}