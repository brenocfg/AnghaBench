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
 int BUFSIZ ; 
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int PAE_INMASK ; 
 int PAE_WAIT_MASK ; 
 int pg_mblen (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 scalar_t__ t_isspace (char*) ; 

__attribute__((used)) static bool
get_nextfield(char **str, char *next)
{
	int			state = PAE_WAIT_MASK;
	int			avail = BUFSIZ;

	while (**str)
	{
		if (state == PAE_WAIT_MASK)
		{
			if (t_iseq(*str, '#'))
				return false;
			else if (!t_isspace(*str))
			{
				int			clen = pg_mblen(*str);

				if (clen < avail)
				{
					COPYCHAR(next, *str);
					next += clen;
					avail -= clen;
				}
				state = PAE_INMASK;
			}
		}
		else					/* state == PAE_INMASK */
		{
			if (t_isspace(*str))
			{
				*next = '\0';
				return true;
			}
			else
			{
				int			clen = pg_mblen(*str);

				if (clen < avail)
				{
					COPYCHAR(next, *str);
					next += clen;
					avail -= clen;
				}
			}
		}
		*str += pg_mblen(*str);
	}

	*next = '\0';

	return (state == PAE_INMASK);	/* OK if we got a nonempty field */
}