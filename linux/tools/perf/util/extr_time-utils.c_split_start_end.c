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
 int ENOMEM ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int split_start_end(char **start, char **end, const char *ostr, char ch)
{
	char *start_str, *end_str;
	char *d, *str;

	if (ostr == NULL || *ostr == '\0')
		return 0;

	/* copy original string because we need to modify it */
	str = strdup(ostr);
	if (str == NULL)
		return -ENOMEM;

	start_str = str;
	d = strchr(start_str, ch);
	if (d) {
		*d = '\0';
		++d;
	}
	end_str = d;

	*start = start_str;
	*end = end_str;

	return 0;
}