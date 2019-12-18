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
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 long simple_strtol (char*,char**,int) ; 

__attribute__((used)) static int match_number(substring_t *s, int *result, int base)
{
	char *endp;
	char *buf;
	int ret;
	long val;

	buf = match_strdup(s);
	if (!buf)
		return -ENOMEM;

	ret = 0;
	val = simple_strtol(buf, &endp, base);
	if (endp == buf)
		ret = -EINVAL;
	else if (val < (long)INT_MIN || val > (long)INT_MAX)
		ret = -ERANGE;
	else
		*result = (int) val;
	kfree(buf);
	return ret;
}