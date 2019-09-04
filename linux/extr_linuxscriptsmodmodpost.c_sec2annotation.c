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
 char* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_exit_sections ; 
 int /*<<< orphan*/  malloc (int) ; 
 scalar_t__ match (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static char *sec2annotation(const char *s)
{
	if (match(s, init_exit_sections)) {
		char *p = NOFAIL(malloc(20));
		char *r = p;

		*p++ = '_';
		*p++ = '_';
		if (*s == '.')
			s++;
		while (*s && *s != '.')
			*p++ = *s++;
		*p = '\0';
		if (*s == '.')
			s++;
		if (strstr(s, "rodata") != NULL)
			strcat(p, "const ");
		else if (strstr(s, "data") != NULL)
			strcat(p, "data ");
		else
			strcat(p, " ");
		return r;
	} else {
		return NOFAIL(strdup(""));
	}
}