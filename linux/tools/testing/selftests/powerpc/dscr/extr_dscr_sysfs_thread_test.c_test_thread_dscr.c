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
 unsigned long get_dscr () ; 
 unsigned long get_dscr_usr () ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long,unsigned long) ; 
 int sched_getcpu () ; 

__attribute__((used)) static int test_thread_dscr(unsigned long val)
{
	unsigned long cur_dscr, cur_dscr_usr;

	cur_dscr = get_dscr();
	cur_dscr_usr = get_dscr_usr();

	if (val != cur_dscr) {
		printf("[cpu %d] Kernel DSCR should be %ld but is %ld\n",
					sched_getcpu(), val, cur_dscr);
		return 1;
	}

	if (val != cur_dscr_usr) {
		printf("[cpu %d] User DSCR should be %ld but is %ld\n",
					sched_getcpu(), val, cur_dscr_usr);
		return 1;
	}
	return 0;
}