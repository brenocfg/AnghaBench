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
 int utf_charcheck (unsigned char*) ; 

__attribute__((used)) static void
mb_utf_validate(unsigned char *pwcs)
{
	unsigned char *p = pwcs;

	while (*pwcs)
	{
		int			len;

		if ((len = utf_charcheck(pwcs)) > 0)
		{
			if (p != pwcs)
			{
				int			i;

				for (i = 0; i < len; i++)
					*p++ = *pwcs++;
			}
			else
			{
				pwcs += len;
				p += len;
			}
		}
		else
			/* we skip the char */
			pwcs++;
	}
	if (p != pwcs)
		*p = '\0';
}