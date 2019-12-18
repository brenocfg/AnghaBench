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
 int /*<<< orphan*/  strcat (char*,char*) ; 
 size_t strcspn (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 char* xmalloc (size_t) ; 

const char *sym_escape_string_value(const char *in)
{
	const char *p;
	size_t reslen;
	char *res;
	size_t l;

	reslen = strlen(in) + strlen("\"\"") + 1;

	p = in;
	for (;;) {
		l = strcspn(p, "\"\\");
		p += l;

		if (p[0] == '\0')
			break;

		reslen++;
		p++;
	}

	res = xmalloc(reslen);
	res[0] = '\0';

	strcat(res, "\"");

	p = in;
	for (;;) {
		l = strcspn(p, "\"\\");
		strncat(res, p, l);
		p += l;

		if (p[0] == '\0')
			break;

		strcat(res, "\\");
		strncat(res, p++, 1);
	}

	strcat(res, "\"");
	return res;
}