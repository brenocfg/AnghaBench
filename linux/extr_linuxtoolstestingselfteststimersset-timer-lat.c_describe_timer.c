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
 int /*<<< orphan*/  clock_id ; 
 char* clockstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

void describe_timer(int flags, int interval)
{
	printf("%-22s %s %s ",
			clockstring(clock_id),
			flags ? "ABSTIME":"RELTIME",
			interval ? "PERIODIC":"ONE-SHOT");
}