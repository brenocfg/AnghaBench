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
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  __fallthrough ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 scalar_t__ islower (char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtoll (char const*,char**,int) ; 

s64 perf_atoll(const char *str)
{
	s64 length;
	char *p;
	char c;

	if (!isdigit(str[0]))
		goto out_err;

	length = strtoll(str, &p, 10);
	switch (c = *p++) {
		case 'b': case 'B':
			if (*p)
				goto out_err;

			__fallthrough;
		case '\0':
			return length;
		default:
			goto out_err;
		/* two-letter suffices */
		case 'k': case 'K':
			length <<= 10;
			break;
		case 'm': case 'M':
			length <<= 20;
			break;
		case 'g': case 'G':
			length <<= 30;
			break;
		case 't': case 'T':
			length <<= 40;
			break;
	}
	/* we want the cases to match */
	if (islower(c)) {
		if (strcmp(p, "b") != 0)
			goto out_err;
	} else {
		if (strcmp(p, "B") != 0)
			goto out_err;
	}
	return length;

out_err:
	return -1;
}