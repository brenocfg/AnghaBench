#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numAttributes; TYPE_1__* attDescs; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char pg_tolower (unsigned char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

int
PQfnumber(const PGresult *res, const char *field_name)
{
	char	   *field_case;
	bool		in_quotes;
	bool		all_lower = true;
	const char *iptr;
	char	   *optr;
	int			i;

	if (!res)
		return -1;

	/*
	 * Note: it is correct to reject a zero-length input string; the proper
	 * input to match a zero-length field name would be "".
	 */
	if (field_name == NULL ||
		field_name[0] == '\0' ||
		res->attDescs == NULL)
		return -1;

	/*
	 * Check if we can avoid the strdup() and related work because the
	 * passed-in string wouldn't be changed before we do the check anyway.
	 */
	for (iptr = field_name; *iptr; iptr++)
	{
		char		c = *iptr;

		if (c == '"' || c != pg_tolower((unsigned char) c))
		{
			all_lower = false;
			break;
		}
	}

	if (all_lower)
		for (i = 0; i < res->numAttributes; i++)
			if (strcmp(field_name, res->attDescs[i].name) == 0)
				return i;

	/* Fall through to the normal check if that didn't work out. */

	/*
	 * Note: this code will not reject partially quoted strings, eg
	 * foo"BAR"foo will become fooBARfoo when it probably ought to be an error
	 * condition.
	 */
	field_case = strdup(field_name);
	if (field_case == NULL)
		return -1;				/* grotty */

	in_quotes = false;
	optr = field_case;
	for (iptr = field_case; *iptr; iptr++)
	{
		char		c = *iptr;

		if (in_quotes)
		{
			if (c == '"')
			{
				if (iptr[1] == '"')
				{
					/* doubled quotes become a single quote */
					*optr++ = '"';
					iptr++;
				}
				else
					in_quotes = false;
			}
			else
				*optr++ = c;
		}
		else if (c == '"')
			in_quotes = true;
		else
		{
			c = pg_tolower((unsigned char) c);
			*optr++ = c;
		}
	}
	*optr = '\0';

	for (i = 0; i < res->numAttributes; i++)
	{
		if (strcmp(field_case, res->attDescs[i].name) == 0)
		{
			free(field_case);
			return i;
		}
	}
	free(field_case);
	return -1;
}