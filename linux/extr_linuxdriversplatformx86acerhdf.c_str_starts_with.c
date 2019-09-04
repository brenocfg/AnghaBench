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
 unsigned long strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,unsigned long) ; 

__attribute__((used)) static int str_starts_with(const char *str, const char *start)
{
	unsigned long str_len = 0, start_len = 0;

	str_len = strlen(str);
	start_len = strlen(start);

	if (str_len >= start_len &&
			!strncmp(str, start, start_len))
		return 1;

	return 0;
}