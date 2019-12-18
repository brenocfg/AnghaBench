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
typedef  int /*<<< orphan*/  NodeTag ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  LEFT_BRACE ; 
 int /*<<< orphan*/  LEFT_PAREN ; 
 int /*<<< orphan*/  OTHER_TOKEN ; 
 int /*<<< orphan*/  RIGHT_PAREN ; 
 int /*<<< orphan*/  T_BitString ; 
 int /*<<< orphan*/  T_Float ; 
 int /*<<< orphan*/  T_Integer ; 
 int /*<<< orphan*/  T_String ; 
 scalar_t__ errno ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  strtoint (char const*,char**,int) ; 

__attribute__((used)) static NodeTag
nodeTokenType(const char *token, int length)
{
	NodeTag		retval;
	const char *numptr;
	int			numlen;

	/*
	 * Check if the token is a number
	 */
	numptr = token;
	numlen = length;
	if (*numptr == '+' || *numptr == '-')
		numptr++, numlen--;
	if ((numlen > 0 && isdigit((unsigned char) *numptr)) ||
		(numlen > 1 && *numptr == '.' && isdigit((unsigned char) numptr[1])))
	{
		/*
		 * Yes.  Figure out whether it is integral or float; this requires
		 * both a syntax check and a range check. strtoint() can do both for
		 * us. We know the token will end at a character that strtoint will
		 * stop at, so we do not need to modify the string.
		 */
		char	   *endptr;

		errno = 0;
		(void) strtoint(token, &endptr, 10);
		if (endptr != token + length || errno == ERANGE)
			return T_Float;
		return T_Integer;
	}

	/*
	 * these three cases do not need length checks, since pg_strtok() will
	 * always treat them as single-byte tokens
	 */
	else if (*token == '(')
		retval = LEFT_PAREN;
	else if (*token == ')')
		retval = RIGHT_PAREN;
	else if (*token == '{')
		retval = LEFT_BRACE;
	else if (*token == '"' && length > 1 && token[length - 1] == '"')
		retval = T_String;
	else if (*token == 'b')
		retval = T_BitString;
	else
		retval = OTHER_TOKEN;
	return retval;
}