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
typedef  enum sched_prio { ____Placeholder_sched_prio } sched_prio ;

/* Variables and functions */
 int SCHED_DEFAULT ; 
 int SCHED_ERR ; 
 int SCHED_HIGH ; 
 int SCHED_LOW ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncasecmp (char*,char const*,int /*<<< orphan*/ ) ; 

enum sched_prio string_to_prio(const char *str)
{
	if (strncasecmp("high", str, strlen(str)) == 0)
		return  SCHED_HIGH;
	else if (strncasecmp("default", str, strlen(str)) == 0)
		return SCHED_DEFAULT;
	else if (strncasecmp("low", str, strlen(str)) == 0)
		return SCHED_LOW;
	else
		return SCHED_ERR;
}