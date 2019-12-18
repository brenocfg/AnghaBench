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
 int /*<<< orphan*/  dawr_supported () ; 
 int runtestsingle (int,int,int) ; 

__attribute__((used)) static int runtest(void)
{
	int rwflag;
	int exclude_user;
	int ret;

	/*
	 * perf defines rwflag as two bits read and write and at least
	 * one must be set.  So range 1-3.
	 */
	for (rwflag = 1 ; rwflag < 4; rwflag++) {
		for (exclude_user = 0 ; exclude_user < 2; exclude_user++) {
			ret = runtestsingle(rwflag, exclude_user, 0);
			if (ret)
				return ret;

			/* if we have the dawr, we can do an array test */
			if (!dawr_supported())
				continue;
			ret = runtestsingle(rwflag, exclude_user, 1);
			if (ret)
				return ret;
		}
	}
	return 0;
}