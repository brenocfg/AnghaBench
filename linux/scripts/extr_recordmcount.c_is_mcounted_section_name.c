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
 scalar_t__ strcmp (char*,char const* const) ; 
 scalar_t__ strncmp (char*,char const* const,int) ; 

__attribute__((used)) static int is_mcounted_section_name(char const *const txtname)
{
	return strncmp(".text",          txtname, 5) == 0 ||
		strcmp(".init.text",     txtname) == 0 ||
		strcmp(".ref.text",      txtname) == 0 ||
		strcmp(".sched.text",    txtname) == 0 ||
		strcmp(".spinlock.text", txtname) == 0 ||
		strcmp(".irqentry.text", txtname) == 0 ||
		strcmp(".softirqentry.text", txtname) == 0 ||
		strcmp(".kprobes.text", txtname) == 0 ||
		strcmp(".cpuidle.text", txtname) == 0;
}