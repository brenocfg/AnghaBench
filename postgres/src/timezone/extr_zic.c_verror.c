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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 char* _ (char*) ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int linenum ; 
 char* rfilename ; 
 int rlinenum ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verror(const char *string, va_list args)
{
	/*
	 * Match the format of "cc" to allow sh users to zic ... 2>&1 | error -t
	 * "*" -v on BSD systems.
	 */
	if (filename)
		fprintf(stderr, _("\"%s\", line %d: "), filename, linenum);
	vfprintf(stderr, string, args);
	if (rfilename != NULL)
		fprintf(stderr, _(" (rule from \"%s\", line %d)"),
				rfilename, rlinenum);
	fprintf(stderr, "\n");
}