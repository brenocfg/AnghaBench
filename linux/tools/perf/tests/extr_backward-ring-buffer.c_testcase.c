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
typedef  int /*<<< orphan*/  proc_name ;

/* Variables and functions */
 int NR_ITERS ; 
 int /*<<< orphan*/  PR_SET_NAME ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void testcase(void)
{
	int i;

	for (i = 0; i < NR_ITERS; i++) {
		char proc_name[15];

		snprintf(proc_name, sizeof(proc_name), "p:%d\n", i);
		prctl(PR_SET_NAME, proc_name);
	}
}