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
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* quote_identifier (char*) ; 
 char* quote_literal_cstr (char*) ; 
 int /*<<< orphan*/  text_format_append_string (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void
text_format_string_conversion(StringInfo buf, char conversion,
							  FmgrInfo *typOutputInfo,
							  Datum value, bool isNull,
							  int flags, int width)
{
	char	   *str;

	/* Handle NULL arguments before trying to stringify the value. */
	if (isNull)
	{
		if (conversion == 's')
			text_format_append_string(buf, "", flags, width);
		else if (conversion == 'L')
			text_format_append_string(buf, "NULL", flags, width);
		else if (conversion == 'I')
			ereport(ERROR,
					(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
					 errmsg("null values cannot be formatted as an SQL identifier")));
		return;
	}

	/* Stringify. */
	str = OutputFunctionCall(typOutputInfo, value);

	/* Escape. */
	if (conversion == 'I')
	{
		/* quote_identifier may or may not allocate a new string. */
		text_format_append_string(buf, quote_identifier(str), flags, width);
	}
	else if (conversion == 'L')
	{
		char	   *qstr = quote_literal_cstr(str);

		text_format_append_string(buf, qstr, flags, width);
		/* quote_literal_cstr() always allocates a new string */
		pfree(qstr);
	}
	else
		text_format_append_string(buf, str, flags, width);

	/* Cleanup. */
	pfree(str);
}