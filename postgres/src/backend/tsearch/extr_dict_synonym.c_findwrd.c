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
typedef  scalar_t__ uint16 ;

/* Variables and functions */
 scalar_t__ TSL_PREFIX ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 scalar_t__ t_isspace (char*) ; 

__attribute__((used)) static char *
findwrd(char *in, char **end, uint16 *flags)
{
	char	   *start;
	char	   *lastchar;

	/* Skip leading spaces */
	while (*in && t_isspace(in))
		in += pg_mblen(in);

	/* Return NULL on empty lines */
	if (*in == '\0')
	{
		*end = NULL;
		return NULL;
	}

	lastchar = start = in;

	/* Find end of word */
	while (*in && !t_isspace(in))
	{
		lastchar = in;
		in += pg_mblen(in);
	}

	if (in - lastchar == 1 && t_iseq(lastchar, '*') && flags)
	{
		*flags = TSL_PREFIX;
		*end = lastchar;
	}
	else
	{
		if (flags)
			*flags = 0;
		*end = in;
	}

	return start;
}