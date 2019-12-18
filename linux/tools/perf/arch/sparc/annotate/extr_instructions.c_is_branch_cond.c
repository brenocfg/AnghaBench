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

__attribute__((used)) static int is_branch_cond(const char *cond)
{
	if (cond[0] == '\0')
		return 1;

	if (cond[0] == 'a' && cond[1] == '\0')
		return 1;

	if (cond[0] == 'c' &&
	    (cond[1] == 'c' || cond[1] == 's') &&
	    cond[2] == '\0')
		return 1;

	if (cond[0] == 'e' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 'q' && cond[2] == '\0')))
		return 1;

	if (cond[0] == 'g' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 't' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == 'u' && cond[3] == '\0')))
		return 1;

	if (cond[0] == 'l' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 't' && cond[2] == '\0') ||
	     (cond[1] == 'u' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == 'u' && cond[3] == '\0')))
		return 1;

	if (cond[0] == 'n' &&
	    (cond[1] == '\0' ||
	     (cond[1] == 'e' && cond[2] == '\0') ||
	     (cond[1] == 'z' && cond[2] == '\0') ||
	     (cond[1] == 'e' && cond[2] == 'g' && cond[3] == '\0')))
		return 1;

	if (cond[0] == 'b' &&
	    cond[1] == 'p' &&
	    cond[2] == 'o' &&
	    cond[3] == 's' &&
	    cond[4] == '\0')
		return 1;

	if (cond[0] == 'v' &&
	    (cond[1] == 'c' || cond[1] == 's') &&
	    cond[2] == '\0')
		return 1;

	if (cond[0] == 'b' &&
	    cond[1] == 'z' &&
	    cond[2] == '\0')
		return 1;

	return 0;
}