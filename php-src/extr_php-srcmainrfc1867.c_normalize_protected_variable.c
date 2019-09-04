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
 int strlen (char*) ; 

__attribute__((used)) static void normalize_protected_variable(char *varname) /* {{{ */
{
	char *s = varname, *index = NULL, *indexend = NULL, *p;

	/* overjump leading space */
	while (*s == ' ') {
		s++;
	}

	/* and remove it */
	if (s != varname) {
		memmove(varname, s, strlen(s)+1);
	}

	for (p = varname; *p && *p != '['; p++) {
		switch(*p) {
			case ' ':
			case '.':
				*p = '_';
				break;
		}
	}

	/* find index */
	index = strchr(varname, '[');
	if (index) {
		index++;
		s = index;
	} else {
		return;
	}

	/* done? */
	while (index) {
		while (*index == ' ' || *index == '\r' || *index == '\n' || *index=='\t') {
			index++;
		}
		indexend = strchr(index, ']');
		indexend = indexend ? indexend + 1 : index + strlen(index);

		if (s != index) {
			memmove(s, index, strlen(index)+1);
			s += indexend-index;
		} else {
			s = indexend;
		}

		if (*s == '[') {
			s++;
			index = s;
		} else {
			index = NULL;
		}
	}
	*s = '\0';
}