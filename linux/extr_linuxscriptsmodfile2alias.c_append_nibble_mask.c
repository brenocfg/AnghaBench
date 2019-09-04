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
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static void append_nibble_mask(char **outp,
			       unsigned int nibble, unsigned int mask)
{
	char *p = *outp;
	unsigned int i;

	switch (mask) {
	case 0:
		*p++ = '?';
		break;

	case 0xf:
		p += sprintf(p, "%X",  nibble);
		break;

	default:
		/*
		 * Dumbly emit a match pattern for all possible matching
		 * digits.  This could be improved in some cases using ranges,
		 * but it has the advantage of being trivially correct, and is
		 * often optimal.
		 */
		*p++ = '[';
		for (i = 0; i < 0x10; i++)
			if ((i & mask) == nibble)
				p += sprintf(p, "%X", i);
		*p++ = ']';
	}

	/* Ensure that the string remains NUL-terminated: */
	*p = '\0';

	/* Advance the caller's end-of-string pointer: */
	*outp = p;
}