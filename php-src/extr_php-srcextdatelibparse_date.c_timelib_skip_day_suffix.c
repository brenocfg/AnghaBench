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
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  timelib_strncasecmp (char*,char*,int) ; 

__attribute__((used)) static void timelib_skip_day_suffix(char **ptr)
{
	if (isspace(**ptr)) {
		return;
	}
	if (!timelib_strncasecmp(*ptr, "nd", 2) || !timelib_strncasecmp(*ptr, "rd", 2) ||!timelib_strncasecmp(*ptr, "st", 2) || !timelib_strncasecmp(*ptr, "th", 2)) {
		*ptr += 2;
	}
}