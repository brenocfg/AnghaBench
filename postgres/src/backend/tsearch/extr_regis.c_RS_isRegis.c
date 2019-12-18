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
 int RS_IN_NONEOF ; 
 int RS_IN_ONEOF ; 
 int RS_IN_ONEOF_IN ; 
 int RS_IN_WAIT ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pg_mblen (char const*) ; 
 scalar_t__ t_isalpha (char const*) ; 
 scalar_t__ t_iseq (char const*,char) ; 

bool
RS_isRegis(const char *str)
{
	int			state = RS_IN_WAIT;
	const char *c = str;

	while (*c)
	{
		if (state == RS_IN_WAIT)
		{
			if (t_isalpha(c))
				 /* okay */ ;
			else if (t_iseq(c, '['))
				state = RS_IN_ONEOF;
			else
				return false;
		}
		else if (state == RS_IN_ONEOF)
		{
			if (t_iseq(c, '^'))
				state = RS_IN_NONEOF;
			else if (t_isalpha(c))
				state = RS_IN_ONEOF_IN;
			else
				return false;
		}
		else if (state == RS_IN_ONEOF_IN || state == RS_IN_NONEOF)
		{
			if (t_isalpha(c))
				 /* okay */ ;
			else if (t_iseq(c, ']'))
				state = RS_IN_WAIT;
			else
				return false;
		}
		else
			elog(ERROR, "internal error in RS_isRegis: state %d", state);
		c += pg_mblen(c);
	}

	return (state == RS_IN_WAIT);
}