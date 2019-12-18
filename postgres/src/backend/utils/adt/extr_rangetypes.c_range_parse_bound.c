#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

__attribute__((used)) static const char *
range_parse_bound(const char *string, const char *ptr,
				  char **bound_str, bool *infinite)
{
	StringInfoData buf;

	/* Check for null: completely empty input means null */
	if (*ptr == ',' || *ptr == ')' || *ptr == ']')
	{
		*bound_str = NULL;
		*infinite = true;
	}
	else
	{
		/* Extract string for this bound */
		bool		inquote = false;

		initStringInfo(&buf);
		while (inquote || !(*ptr == ',' || *ptr == ')' || *ptr == ']'))
		{
			char		ch = *ptr++;

			if (ch == '\0')
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("malformed range literal: \"%s\"",
								string),
						 errdetail("Unexpected end of input.")));
			if (ch == '\\')
			{
				if (*ptr == '\0')
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
							 errmsg("malformed range literal: \"%s\"",
									string),
							 errdetail("Unexpected end of input.")));
				appendStringInfoChar(&buf, *ptr++);
			}
			else if (ch == '"')
			{
				if (!inquote)
					inquote = true;
				else if (*ptr == '"')
				{
					/* doubled quote within quote sequence */
					appendStringInfoChar(&buf, *ptr++);
				}
				else
					inquote = false;
			}
			else
				appendStringInfoChar(&buf, ch);
		}

		*bound_str = buf.data;
		*infinite = false;
	}

	return ptr;
}