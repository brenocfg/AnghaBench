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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
read_gucstate(char **srcptr, char *srcend)
{
	char	   *retptr = *srcptr;
	char	   *ptr;

	if (*srcptr >= srcend)
		elog(ERROR, "incomplete GUC state");

	/* The string variables are all null terminated */
	for (ptr = *srcptr; ptr < srcend && *ptr != '\0'; ptr++)
		;

	if (ptr >= srcend)
		elog(ERROR, "could not find null terminator in GUC state");

	/* Set the new position to the byte following the terminating NUL */
	*srcptr = ptr + 1;

	return retptr;
}