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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 

char *strdup_esc(const char *str)
{
	char *s, *d, *p, *ret = strdup(str);

	if (!ret)
		return NULL;

	d = strchr(ret, '\\');
	if (!d)
		return ret;

	s = d + 1;
	do {
		if (*s == '\0') {
			*d = '\0';
			break;
		}
		p = strchr(s + 1, '\\');
		if (p) {
			memmove(d, s, p - s);
			d += p - s;
			s = p + 1;
		} else
			memmove(d, s, strlen(s) + 1);
	} while (p);

	return ret;
}