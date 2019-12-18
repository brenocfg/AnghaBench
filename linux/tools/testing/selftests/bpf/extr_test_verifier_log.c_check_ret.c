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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void check_ret(int ret, int exp_errno)
{
	if (ret > 0) {
		close(ret);
		err("broken sample loaded successfully!?\n");
		exit(1);
	}

	if (!ret || errno != exp_errno) {
		err("Program load returned: ret:%d/errno:%d, expected ret:%d/errno:%d\n",
		    ret, errno, -1, exp_errno);
		exit(1);
	}
}