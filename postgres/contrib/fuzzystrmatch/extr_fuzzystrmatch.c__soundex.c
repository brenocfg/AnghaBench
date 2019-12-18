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
 int /*<<< orphan*/  AssertArg (char const*) ; 
 size_t SOUNDEX_LEN ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ soundex_code (char const) ; 
 scalar_t__ toupper (unsigned char) ; 

__attribute__((used)) static void
_soundex(const char *instr, char *outstr)
{
	int			count;

	AssertArg(instr);
	AssertArg(outstr);

	outstr[SOUNDEX_LEN] = '\0';

	/* Skip leading non-alphabetic characters */
	while (!isalpha((unsigned char) instr[0]) && instr[0])
		++instr;

	/* No string left */
	if (!instr[0])
	{
		outstr[0] = (char) 0;
		return;
	}

	/* Take the first letter as is */
	*outstr++ = (char) toupper((unsigned char) *instr++);

	count = 1;
	while (*instr && count < SOUNDEX_LEN)
	{
		if (isalpha((unsigned char) *instr) &&
			soundex_code(*instr) != soundex_code(*(instr - 1)))
		{
			*outstr = soundex_code(instr[0]);
			if (*outstr != '0')
			{
				++outstr;
				++count;
			}
		}
		++instr;
	}

	/* Fill with 0's */
	while (count < SOUNDEX_LEN)
	{
		*outstr = '0';
		++outstr;
		++count;
	}
}