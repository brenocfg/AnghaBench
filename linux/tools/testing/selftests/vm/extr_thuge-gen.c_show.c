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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 unsigned long getpagesize () ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  system (char*) ; 

void show(unsigned long ps)
{
	char buf[100];
	if (ps == getpagesize())
		return;
	printf("%luMB: ", ps >> 20);
	fflush(stdout);
	snprintf(buf, sizeof buf,
		"cat /sys/kernel/mm/hugepages/hugepages-%lukB/free_hugepages",
		ps >> 10);
	system(buf);
}