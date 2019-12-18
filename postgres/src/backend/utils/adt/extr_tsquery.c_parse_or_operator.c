#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buf; scalar_t__ in_quotes; } ;
typedef  TYPE_1__* TSQueryParserState ;

/* Variables and functions */
 int /*<<< orphan*/  pg_mblen (char*) ; 
 scalar_t__ pg_strncasecmp (char*,char*,int) ; 
 scalar_t__ t_isalpha (char*) ; 
 scalar_t__ t_isdigit (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 int /*<<< orphan*/  t_isspace (char*) ; 

__attribute__((used)) static bool
parse_or_operator(TSQueryParserState pstate)
{
	char	   *ptr = pstate->buf;

	if (pstate->in_quotes)
		return false;

	/* it should begin with "OR" literal */
	if (pg_strncasecmp(ptr, "or", 2) != 0)
		return false;

	ptr += 2;

	/*
	 * it shouldn't be a part of any word but somewhere later it should be
	 * some operand
	 */
	if (*ptr == '\0')			/* no operand */
		return false;

	/* it shouldn't be a part of any word */
	if (t_iseq(ptr, '-') || t_iseq(ptr, '_') || t_isalpha(ptr) || t_isdigit(ptr))
		return false;

	for (;;)
	{
		ptr += pg_mblen(ptr);

		if (*ptr == '\0')		/* got end of string without operand */
			return false;

		/*
		 * Suppose, we found an operand, but could be a not correct operand.
		 * So we still treat OR literal as operation with possibly incorrect
		 * operand and  will not search it as lexeme
		 */
		if (!t_isspace(ptr))
			break;
	}

	pstate->buf += 2;
	return true;
}