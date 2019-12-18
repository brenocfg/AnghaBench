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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int INT_MIN ; 
 int TEXT_FORMAT_FLAG_MINUS ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int pg_mbstrlen (char const*) ; 

__attribute__((used)) static void
text_format_append_string(StringInfo buf, const char *str,
						  int flags, int width)
{
	bool		align_to_left = false;
	int			len;

	/* fast path for typical easy case */
	if (width == 0)
	{
		appendStringInfoString(buf, str);
		return;
	}

	if (width < 0)
	{
		/* Negative width: implicit '-' flag, then take absolute value */
		align_to_left = true;
		/* -INT_MIN is undefined */
		if (width <= INT_MIN)
			ereport(ERROR,
					(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
					 errmsg("number is out of range")));
		width = -width;
	}
	else if (flags & TEXT_FORMAT_FLAG_MINUS)
		align_to_left = true;

	len = pg_mbstrlen(str);
	if (align_to_left)
	{
		/* left justify */
		appendStringInfoString(buf, str);
		if (len < width)
			appendStringInfoSpaces(buf, width - len);
	}
	else
	{
		/* right justify */
		if (len < width)
			appendStringInfoSpaces(buf, width - len);
		appendStringInfoString(buf, str);
	}
}