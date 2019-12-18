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
 scalar_t__ pager_in_use () ; 
 int /*<<< orphan*/  print_tool_event (char*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void print_tool_events(const char *event_glob, bool name_only)
{
	print_tool_event("duration_time", event_glob, name_only);
	if (pager_in_use())
		printf("\n");
}