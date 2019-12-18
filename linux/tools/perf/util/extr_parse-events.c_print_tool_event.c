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
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  strglobmatch (char const*,char const*) ; 

__attribute__((used)) static void print_tool_event(const char *name, const char *event_glob,
			     bool name_only)
{
	if (event_glob && !strglobmatch(name, event_glob))
		return;
	if (name_only)
		printf("%s ", name);
	else
		printf("  %-50s [%s]\n", name, "Tool event");

}