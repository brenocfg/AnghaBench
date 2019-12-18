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
typedef  scalar_t__ ArrayParseState ;

/* Variables and functions */
 scalar_t__ ARRAY_ELEM_COMPLETED ; 
 scalar_t__ ARRAY_ELEM_DELIMITED ; 
 scalar_t__ ARRAY_ELEM_STARTED ; 
 scalar_t__ ARRAY_LEVEL_COMPLETED ; 
 scalar_t__ ARRAY_LEVEL_DELIMITED ; 
 scalar_t__ ARRAY_LEVEL_STARTED ; 
 scalar_t__ ARRAY_NO_LEVEL ; 
 scalar_t__ ARRAY_QUOTED_ELEM_COMPLETED ; 
 scalar_t__ ARRAY_QUOTED_ELEM_STARTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXDIM ; 
 int /*<<< orphan*/  array_isspace (char const) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static int
ArrayCount(const char *str, int *dim, char typdelim)
{
	int			nest_level = 0,
				i;
	int			ndim = 1,
				temp[MAXDIM],
				nelems[MAXDIM],
				nelems_last[MAXDIM];
	bool		in_quotes = false;
	bool		eoArray = false;
	bool		empty_array = true;
	const char *ptr;
	ArrayParseState parse_state = ARRAY_NO_LEVEL;

	for (i = 0; i < MAXDIM; ++i)
	{
		temp[i] = dim[i] = nelems_last[i] = 0;
		nelems[i] = 1;
	}

	ptr = str;
	while (!eoArray)
	{
		bool		itemdone = false;

		while (!itemdone)
		{
			if (parse_state == ARRAY_ELEM_STARTED ||
				parse_state == ARRAY_QUOTED_ELEM_STARTED)
				empty_array = false;

			switch (*ptr)
			{
				case '\0':
					/* Signal a premature end of the string */
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
							 errmsg("malformed array literal: \"%s\"", str),
							 errdetail("Unexpected end of input.")));
					break;
				case '\\':

					/*
					 * An escape must be after a level start, after an element
					 * start, or after an element delimiter. In any case we
					 * now must be past an element start.
					 */
					if (parse_state != ARRAY_LEVEL_STARTED &&
						parse_state != ARRAY_ELEM_STARTED &&
						parse_state != ARRAY_QUOTED_ELEM_STARTED &&
						parse_state != ARRAY_ELEM_DELIMITED)
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								 errmsg("malformed array literal: \"%s\"", str),
								 errdetail("Unexpected \"%c\" character.",
										   '\\')));
					if (parse_state != ARRAY_QUOTED_ELEM_STARTED)
						parse_state = ARRAY_ELEM_STARTED;
					/* skip the escaped character */
					if (*(ptr + 1))
						ptr++;
					else
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								 errmsg("malformed array literal: \"%s\"", str),
								 errdetail("Unexpected end of input.")));
					break;
				case '"':

					/*
					 * A quote must be after a level start, after a quoted
					 * element start, or after an element delimiter. In any
					 * case we now must be past an element start.
					 */
					if (parse_state != ARRAY_LEVEL_STARTED &&
						parse_state != ARRAY_QUOTED_ELEM_STARTED &&
						parse_state != ARRAY_ELEM_DELIMITED)
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								 errmsg("malformed array literal: \"%s\"", str),
								 errdetail("Unexpected array element.")));
					in_quotes = !in_quotes;
					if (in_quotes)
						parse_state = ARRAY_QUOTED_ELEM_STARTED;
					else
						parse_state = ARRAY_QUOTED_ELEM_COMPLETED;
					break;
				case '{':
					if (!in_quotes)
					{
						/*
						 * A left brace can occur if no nesting has occurred
						 * yet, after a level start, or after a level
						 * delimiter.
						 */
						if (parse_state != ARRAY_NO_LEVEL &&
							parse_state != ARRAY_LEVEL_STARTED &&
							parse_state != ARRAY_LEVEL_DELIMITED)
							ereport(ERROR,
									(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
									 errmsg("malformed array literal: \"%s\"", str),
									 errdetail("Unexpected \"%c\" character.",
											   '{')));
						parse_state = ARRAY_LEVEL_STARTED;
						if (nest_level >= MAXDIM)
							ereport(ERROR,
									(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
									 errmsg("number of array dimensions (%d) exceeds the maximum allowed (%d)",
											nest_level + 1, MAXDIM)));
						temp[nest_level] = 0;
						nest_level++;
						if (ndim < nest_level)
							ndim = nest_level;
					}
					break;
				case '}':
					if (!in_quotes)
					{
						/*
						 * A right brace can occur after an element start, an
						 * element completion, a quoted element completion, or
						 * a level completion.
						 */
						if (parse_state != ARRAY_ELEM_STARTED &&
							parse_state != ARRAY_ELEM_COMPLETED &&
							parse_state != ARRAY_QUOTED_ELEM_COMPLETED &&
							parse_state != ARRAY_LEVEL_COMPLETED &&
							!(nest_level == 1 && parse_state == ARRAY_LEVEL_STARTED))
							ereport(ERROR,
									(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
									 errmsg("malformed array literal: \"%s\"", str),
									 errdetail("Unexpected \"%c\" character.",
											   '}')));
						parse_state = ARRAY_LEVEL_COMPLETED;
						if (nest_level == 0)
							ereport(ERROR,
									(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
									 errmsg("malformed array literal: \"%s\"", str),
									 errdetail("Unmatched \"%c\" character.", '}')));
						nest_level--;

						if (nelems_last[nest_level] != 0 &&
							nelems[nest_level] != nelems_last[nest_level])
							ereport(ERROR,
									(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
									 errmsg("malformed array literal: \"%s\"", str),
									 errdetail("Multidimensional arrays must have "
											   "sub-arrays with matching "
											   "dimensions.")));
						nelems_last[nest_level] = nelems[nest_level];
						nelems[nest_level] = 1;
						if (nest_level == 0)
							eoArray = itemdone = true;
						else
						{
							/*
							 * We don't set itemdone here; see comments in
							 * ReadArrayStr
							 */
							temp[nest_level - 1]++;
						}
					}
					break;
				default:
					if (!in_quotes)
					{
						if (*ptr == typdelim)
						{
							/*
							 * Delimiters can occur after an element start, an
							 * element completion, a quoted element
							 * completion, or a level completion.
							 */
							if (parse_state != ARRAY_ELEM_STARTED &&
								parse_state != ARRAY_ELEM_COMPLETED &&
								parse_state != ARRAY_QUOTED_ELEM_COMPLETED &&
								parse_state != ARRAY_LEVEL_COMPLETED)
								ereport(ERROR,
										(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
										 errmsg("malformed array literal: \"%s\"", str),
										 errdetail("Unexpected \"%c\" character.",
												   typdelim)));
							if (parse_state == ARRAY_LEVEL_COMPLETED)
								parse_state = ARRAY_LEVEL_DELIMITED;
							else
								parse_state = ARRAY_ELEM_DELIMITED;
							itemdone = true;
							nelems[nest_level - 1]++;
						}
						else if (!array_isspace(*ptr))
						{
							/*
							 * Other non-space characters must be after a
							 * level start, after an element start, or after
							 * an element delimiter. In any case we now must
							 * be past an element start.
							 */
							if (parse_state != ARRAY_LEVEL_STARTED &&
								parse_state != ARRAY_ELEM_STARTED &&
								parse_state != ARRAY_ELEM_DELIMITED)
								ereport(ERROR,
										(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
										 errmsg("malformed array literal: \"%s\"", str),
										 errdetail("Unexpected array element.")));
							parse_state = ARRAY_ELEM_STARTED;
						}
					}
					break;
			}
			if (!itemdone)
				ptr++;
		}
		temp[ndim - 1]++;
		ptr++;
	}

	/* only whitespace is allowed after the closing brace */
	while (*ptr)
	{
		if (!array_isspace(*ptr++))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("malformed array literal: \"%s\"", str),
					 errdetail("Junk after closing right brace.")));
	}

	/* special case for an empty array */
	if (empty_array)
		return 0;

	for (i = 0; i < ndim; ++i)
		dim[i] = temp[i];

	return ndim;
}