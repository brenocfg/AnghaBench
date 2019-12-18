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
typedef  int /*<<< orphan*/  ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int OIDCHARS ; 
 int forkname_chars (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 

bool
parse_filename_for_nontemp_relation(const char *name, int *oidchars,
									ForkNumber *fork)
{
	int			pos;

	/* Look for a non-empty string of digits (that isn't too long). */
	for (pos = 0; isdigit((unsigned char) name[pos]); ++pos)
		;
	if (pos == 0 || pos > OIDCHARS)
		return false;
	*oidchars = pos;

	/* Check for a fork name. */
	if (name[pos] != '_')
		*fork = MAIN_FORKNUM;
	else
	{
		int			forkchar;

		forkchar = forkname_chars(&name[pos + 1], fork);
		if (forkchar <= 0)
			return false;
		pos += forkchar + 1;
	}

	/* Check for a segment number. */
	if (name[pos] == '.')
	{
		int			segchar;

		for (segchar = 1; isdigit((unsigned char) name[pos + segchar]); ++segchar)
			;
		if (segchar <= 1)
			return false;
		pos += segchar;
	}

	/* Now we should be at the end. */
	if (name[pos] != '\0')
		return false;
	return true;
}