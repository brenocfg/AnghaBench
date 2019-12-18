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
 int tolower (int) ; 
 int /*<<< orphan*/  xprintf (char*,...) ; 
 int /*<<< orphan*/  xputchar (int) ; 

__attribute__((used)) static void print_dep(const char *m, int slen, const char *dir)
{
	int c, prev_c = '/', i;

	xprintf("    $(wildcard %s/", dir);
	for (i = 0; i < slen; i++) {
		c = m[i];
		if (c == '_')
			c = '/';
		else
			c = tolower(c);
		if (c != '/' || prev_c != '/')
			xputchar(c);
		prev_c = c;
	}
	xprintf(".h) \\\n");
}