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
 int forkname_chars (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 

bool
looks_like_temp_rel_name(const char *name)
{
	int			pos;
	int			savepos;

	/* Must start with "t". */
	if (name[0] != 't')
		return false;

	/* Followed by a non-empty string of digits and then an underscore. */
	for (pos = 1; isdigit((unsigned char) name[pos]); ++pos)
		;
	if (pos == 1 || name[pos] != '_')
		return false;

	/* Followed by another nonempty string of digits. */
	for (savepos = ++pos; isdigit((unsigned char) name[pos]); ++pos)
		;
	if (savepos == pos)
		return false;

	/* We might have _forkname or .segment or both. */
	if (name[pos] == '_')
	{
		int			forkchar = forkname_chars(&name[pos + 1], NULL);

		if (forkchar <= 0)
			return false;
		pos += forkchar + 1;
	}
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