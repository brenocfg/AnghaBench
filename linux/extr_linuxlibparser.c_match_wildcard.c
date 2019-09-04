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

bool match_wildcard(const char *pattern, const char *str)
{
	const char *s = str;
	const char *p = pattern;
	bool star = false;

	while (*s) {
		switch (*p) {
		case '?':
			s++;
			p++;
			break;
		case '*':
			star = true;
			str = s;
			if (!*++p)
				return true;
			pattern = p;
			break;
		default:
			if (*s == *p) {
				s++;
				p++;
			} else {
				if (!star)
					return false;
				str++;
				s = str;
				p = pattern;
			}
			break;
		}
	}

	if (*p == '*')
		++p;
	return !*p;
}