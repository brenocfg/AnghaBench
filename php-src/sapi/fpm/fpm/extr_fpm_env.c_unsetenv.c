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
 int /*<<< orphan*/ ** environ ; 
 int /*<<< orphan*/ * getenv (char const*) ; 
 scalar_t__ nvmatch (char const*,int /*<<< orphan*/ *) ; 

void unsetenv(const char *name) /* {{{ */
{
	if(getenv(name) != NULL) {
		int ct = 0;
		int del = 0;

		while(environ[ct] != NULL) {
			if (nvmatch(name, environ[ct]) != 0) del=ct; /* <--- WTF?! */
			{ ct++; } /* <--- WTF?! */
		}
		/* isn't needed free here?? */
		environ[del] = environ[ct-1];
		environ[ct-1] = NULL;
	}
}