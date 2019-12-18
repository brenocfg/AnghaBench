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
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 char RANGE_EMPTY ; 
 int /*<<< orphan*/  RANGE_EMPTY_LITERAL ; 
 char RANGE_LB_INC ; 
 char RANGE_LB_INF ; 
 char RANGE_UB_INC ; 
 char RANGE_UB_INF ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ pg_strncasecmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* range_parse_bound (char const*,char const*,char**,int*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
range_parse(const char *string, char *flags, char **lbound_str,
			char **ubound_str)
{
	const char *ptr = string;
	bool		infinite;

	*flags = 0;

	/* consume whitespace */
	while (*ptr != '\0' && isspace((unsigned char) *ptr))
		ptr++;

	/* check for empty range */
	if (pg_strncasecmp(ptr, RANGE_EMPTY_LITERAL,
					   strlen(RANGE_EMPTY_LITERAL)) == 0)
	{
		*flags = RANGE_EMPTY;
		*lbound_str = NULL;
		*ubound_str = NULL;

		ptr += strlen(RANGE_EMPTY_LITERAL);

		/* the rest should be whitespace */
		while (*ptr != '\0' && isspace((unsigned char) *ptr))
			ptr++;

		/* should have consumed everything */
		if (*ptr != '\0')
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("malformed range literal: \"%s\"",
							string),
					 errdetail("Junk after \"empty\" key word.")));

		return;
	}

	if (*ptr == '[')
	{
		*flags |= RANGE_LB_INC;
		ptr++;
	}
	else if (*ptr == '(')
		ptr++;
	else
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("malformed range literal: \"%s\"",
						string),
				 errdetail("Missing left parenthesis or bracket.")));

	ptr = range_parse_bound(string, ptr, lbound_str, &infinite);
	if (infinite)
		*flags |= RANGE_LB_INF;

	if (*ptr == ',')
		ptr++;
	else
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("malformed range literal: \"%s\"",
						string),
				 errdetail("Missing comma after lower bound.")));

	ptr = range_parse_bound(string, ptr, ubound_str, &infinite);
	if (infinite)
		*flags |= RANGE_UB_INF;

	if (*ptr == ']')
	{
		*flags |= RANGE_UB_INC;
		ptr++;
	}
	else if (*ptr == ')')
		ptr++;
	else						/* must be a comma */
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("malformed range literal: \"%s\"",
						string),
				 errdetail("Too many commas.")));

	/* consume whitespace */
	while (*ptr != '\0' && isspace((unsigned char) *ptr))
		ptr++;

	if (*ptr != '\0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("malformed range literal: \"%s\"",
						string),
				 errdetail("Junk after right parenthesis or bracket.")));
}