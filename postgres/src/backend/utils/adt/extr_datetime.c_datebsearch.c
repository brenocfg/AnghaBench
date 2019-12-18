#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* token; } ;
typedef  TYPE_1__ datetkn ;

/* Variables and functions */
 int /*<<< orphan*/  TOKMAXLEN ; 
 int strncmp (char const*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const datetkn *
datebsearch(const char *key, const datetkn *base, int nel)
{
	if (nel > 0)
	{
		const datetkn *last = base + nel - 1,
				   *position;
		int			result;

		while (last >= base)
		{
			position = base + ((last - base) >> 1);
			/* precheck the first character for a bit of extra speed */
			result = (int) key[0] - (int) position->token[0];
			if (result == 0)
			{
				/* use strncmp so that we match truncated tokens */
				result = strncmp(key, position->token, TOKMAXLEN);
				if (result == 0)
					return position;
			}
			if (result < 0)
				last = position - 1;
			else
				base = position + 1;
		}
	}
	return NULL;
}