#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

void
pg_split_opts(char **argv, int *argcp, const char *optstr)
{
	StringInfoData s;

	initStringInfo(&s);

	while (*optstr)
	{
		bool		last_was_escape = false;

		resetStringInfo(&s);

		/* skip over leading space */
		while (isspace((unsigned char) *optstr))
			optstr++;

		if (*optstr == '\0')
			break;

		/*
		 * Parse a single option, stopping at the first space, unless it's
		 * escaped.
		 */
		while (*optstr)
		{
			if (isspace((unsigned char) *optstr) && !last_was_escape)
				break;

			if (!last_was_escape && *optstr == '\\')
				last_was_escape = true;
			else
			{
				last_was_escape = false;
				appendStringInfoChar(&s, *optstr);
			}

			optstr++;
		}

		/* now store the option in the next argv[] position */
		argv[(*argcp)++] = pstrdup(s.data);
	}

	pfree(s.data);
}