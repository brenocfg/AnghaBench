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
 int /*<<< orphan*/  ADVANCE_PARSE_POINTER (char const*,char const*) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int TEXT_FORMAT_FLAG_MINUS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ text_format_parse_digits (char const**,char const*,int*) ; 

__attribute__((used)) static const char *
text_format_parse_format(const char *start_ptr, const char *end_ptr,
						 int *argpos, int *widthpos,
						 int *flags, int *width)
{
	const char *cp = start_ptr;
	int			n;

	/* set defaults for output parameters */
	*argpos = -1;
	*widthpos = -1;
	*flags = 0;
	*width = 0;

	/* try to identify first number */
	if (text_format_parse_digits(&cp, end_ptr, &n))
	{
		if (*cp != '$')
		{
			/* Must be just a width and a type, so we're done */
			*width = n;
			return cp;
		}
		/* The number was argument position */
		*argpos = n;
		/* Explicit 0 for argument index is immediately refused */
		if (n == 0)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("format specifies argument 0, but arguments are numbered from 1")));
		ADVANCE_PARSE_POINTER(cp, end_ptr);
	}

	/* Handle flags (only minus is supported now) */
	while (*cp == '-')
	{
		*flags |= TEXT_FORMAT_FLAG_MINUS;
		ADVANCE_PARSE_POINTER(cp, end_ptr);
	}

	if (*cp == '*')
	{
		/* Handle indirect width */
		ADVANCE_PARSE_POINTER(cp, end_ptr);
		if (text_format_parse_digits(&cp, end_ptr, &n))
		{
			/* number in this position must be closed by $ */
			if (*cp != '$')
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("width argument position must be ended by \"$\"")));
			/* The number was width argument position */
			*widthpos = n;
			/* Explicit 0 for argument index is immediately refused */
			if (n == 0)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("format specifies argument 0, but arguments are numbered from 1")));
			ADVANCE_PARSE_POINTER(cp, end_ptr);
		}
		else
			*widthpos = 0;		/* width's argument position is unspecified */
	}
	else
	{
		/* Check for direct width specification */
		if (text_format_parse_digits(&cp, end_ptr, &n))
			*width = n;
	}

	/* cp should now be pointing at type character */
	return cp;
}