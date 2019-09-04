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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 char toupper (char) ; 

__attribute__((used)) static char *stoupperx(const char *s)
{
	char *s2 = strdup(s);
	char *p;

	if (!s2) {
		fprintf(stderr, "%s:  out of memory\n", progname);
		exit(3);
	}

	for (p = s2; *p; p++)
		*p = toupper(*p);
	return s2;
}