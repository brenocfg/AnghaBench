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
 int alarmcount ; 
 int /*<<< orphan*/  describe_timer (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int check_alarmcount(int flags, int interval)
{
	describe_timer(flags, interval);
	printf("count: %19d : ", alarmcount);
	if (alarmcount == 1) {
		printf("[OK]\n");
		return 0;
	}
	printf("[FAILED]\n");
	return -1;
}