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
typedef  int /*<<< orphan*/  float8 ;

/* Variables and functions */
 int /*<<< orphan*/  DELIM ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 char LDELIM ; 
 int /*<<< orphan*/  RDELIM ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 
 int /*<<< orphan*/  float8in_internal (char*,char**,char const*,char const*) ; 
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static void
pair_decode(char *str, float8 *x, float8 *y, char **endptr_p,
			const char *type_name, const char *orig_string)
{
	bool		has_delim;

	while (isspace((unsigned char) *str))
		str++;
	if ((has_delim = (*str == LDELIM)))
		str++;

	*x = float8in_internal(str, &str, type_name, orig_string);

	if (*str++ != DELIM)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						type_name, orig_string)));

	*y = float8in_internal(str, &str, type_name, orig_string);

	if (has_delim)
	{
		if (*str++ != RDELIM)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("invalid input syntax for type %s: \"%s\"",
							type_name, orig_string)));
		while (isspace((unsigned char) *str))
			str++;
	}

	/* report stopping point if wanted, else complain if not end of string */
	if (endptr_p)
		*endptr_p = str;
	else if (*str != '\0')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						type_name, orig_string)));
}