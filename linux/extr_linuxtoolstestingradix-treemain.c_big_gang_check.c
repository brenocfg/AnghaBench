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
 int /*<<< orphan*/  __big_gang_check () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printv (int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

void big_gang_check(bool long_run)
{
	int i;

	for (i = 0; i < (long_run ? 1000 : 3); i++) {
		__big_gang_check();
		printv(2, "%d ", i);
		fflush(stdout);
	}
}