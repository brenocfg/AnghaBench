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
 unsigned char CASE_DELIMITER ; 
 int /*<<< orphan*/ * _ebc_tolower ; 
 int /*<<< orphan*/ * _ebc_toupper ; 
 scalar_t__ sclp_tty_tolower ; 

__attribute__((used)) static int sclp_switch_cases(unsigned char *buf, int count)
{
	unsigned char *ip, *op;
	int toggle;

	/* initially changing case is off */
	toggle = 0;
	ip = op = buf;
	while (count-- > 0) {
		/* compare with special character */
		if (*ip == CASE_DELIMITER) {
			/* followed by another special character? */
			if (count && ip[1] == CASE_DELIMITER) {
				/*
				 * ... then put a single copy of the special
				 * character to the output string
				 */
				*op++ = *ip++;
				count--;
			} else
				/*
				 * ... special character follower by a normal
				 * character toggles the case change behaviour
				 */
				toggle = ~toggle;
			/* skip special character */
			ip++;
		} else
			/* not the special character */
			if (toggle)
				/* but case switching is on */
				if (sclp_tty_tolower)
					/* switch to uppercase */
					*op++ = _ebc_toupper[(int) *ip++];
				else
					/* switch to lowercase */
					*op++ = _ebc_tolower[(int) *ip++];
			else
				/* no case switching, copy the character */
				*op++ = *ip++;
	}
	/* return length of reformatted string. */
	return op - buf;
}