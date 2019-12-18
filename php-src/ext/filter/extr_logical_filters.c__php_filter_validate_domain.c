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
typedef  int zend_long ;

/* Variables and functions */
 int FILTER_FLAG_HOSTNAME ; 
 int /*<<< orphan*/  isalnum (int) ; 

__attribute__((used)) static int _php_filter_validate_domain(char * domain, int len, zend_long flags) /* {{{ */
{
	char *e, *s, *t;
	size_t l;
	int hostname = flags & FILTER_FLAG_HOSTNAME;
	unsigned char i = 1;

	s = domain;
	l = len;
	e = domain + l;
	t = e - 1;

	/* Ignore trailing dot */
	if (*t == '.') {
		e = t;
		l--;
	}

	/* The total length cannot exceed 253 characters (final dot not included) */
	if (l > 253) {
		return 0;
	}

	/* First char must be alphanumeric */
	if(*s == '.' || (hostname && !isalnum((int)*(unsigned char *)s))) {
		return 0;
	}

	while (s < e) {
		if (*s == '.') {
			/* The first and the last character of a label must be alphanumeric */
			if (*(s + 1) == '.' || (hostname && (!isalnum((int)*(unsigned char *)(s - 1)) || !isalnum((int)*(unsigned char *)(s + 1))))) {
				return 0;
			}

			/* Reset label length counter */
			i = 1;
		} else {
			if (i > 63 || (hostname && *s != '-' && !isalnum((int)*(unsigned char *)s))) {
				return 0;
			}

			i++;
		}

		s++;
	}

	return 1;
}